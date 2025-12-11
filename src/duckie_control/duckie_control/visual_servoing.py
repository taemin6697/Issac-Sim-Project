import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from geometry_msgs.msg import Twist
from cv_bridge import CvBridge
import cv2
import numpy as np

class DuckiebotChaser(Node):
    def __init__(self):
        super().__init__('duckiebot_chaser')
        
        # 1. Subscriber: Subscribe to camera topic
        self.subscription = self.create_subscription(
            Image,
            '/duckie/camera/image_raw',
            self.image_callback,
            10)
            
        # 2. Publisher: Publish motor commands
        self.publisher = self.create_publisher(Twist, '/duckie/cmd_vel', 10)
        
        self.bridge = CvBridge()
        self.get_logger().info("Duckiebot Chaser Started! Waiting for Red Cube...")

    def image_callback(self, msg):
        # --- A. Convert ROS Image to OpenCV ---
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")
        except Exception as e:
            self.get_logger().error(f"Image conversion failed: {e}")
            return

        # --- B. Color Filtering (Red Detection) ---
        hsv = cv2.cvtColor(cv_image, cv2.COLOR_BGR2HSV)
        
        # Red color wraps around 0 and 180 in HSV
        # Lower Red (0-10)
        lower_red1 = np.array([0, 100, 100])
        upper_red1 = np.array([10, 255, 255])
        # Upper Red (170-180)
        lower_red2 = np.array([170, 100, 100])
        upper_red2 = np.array([180, 255, 255])
        
        mask1 = cv2.inRange(hsv, lower_red1, upper_red1)
        mask2 = cv2.inRange(hsv, lower_red2, upper_red2)
        mask = mask1 + mask2  # Combine masks

        # --- C. Find Largest Contour ---
        contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        
        twist = Twist() # Default: Stop
        
        if len(contours) > 0:
            # Get the largest contour by area
            c = max(contours, key=cv2.contourArea)
            area = cv2.contourArea(c)
            
            # Ignore small noise (area must be > 500)
            if area > 500:
                # --- D. Calculate Centroid ---
                M = cv2.moments(c)
                if M['m00'] > 0:
                    cx = int(M['m10'] / M['m00']) # X center of object
                    cy = int(M['m01'] / M['m00']) # Y center of object
                    
                    # Draw visual aids on image
                    cv2.drawContours(cv_image, [c], -1, (0, 255, 0), 2)
                    cv2.circle(cv_image, (cx, cy), 5, (255, 0, 0), -1)

                    # --- E. Control Algorithm (P-Control) ---
                    height, width, _ = cv_image.shape
                    center_x = width // 2  # Screen center
                    
                    # Calculate error (Screen Center - Object Center)
                    # Positive error -> Turn Left
                    # Negative error -> Turn Right
                    err_x = center_x - cx
                    
                    # 1. Angular Control (Proportional Gain)
                    twist.angular.z = float(err_x) * 0.005
                    
                    # 2. Linear Control (Distance Keep)
                    # If object is far (small area), move forward
                    if area < 150000: 
                        twist.linear.x = 0.5
                    else:             
                        # If object is close (large area), stop
                        twist.linear.x = 0.0
                        
        else:
            # If no red object found, stop
            twist.linear.x = 0.0
            twist.angular.z = 0.0

        # --- F. Publish Command & Show Image ---
        self.publisher.publish(twist)
        
        # Display image window (for debugging)
        cv2.imshow("Duckiebot Vision", cv_image)
        cv2.waitKey(1)

def main(args=None):
    rclpy.init(args=args)
    node = DuckiebotChaser()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        # Stop robot on shutdown
        stop_twist = Twist()
        node.publisher.publish(stop_twist)
        node.destroy_node()
        rclpy.shutdown()
        cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
