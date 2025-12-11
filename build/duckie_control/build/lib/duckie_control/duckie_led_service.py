import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
# Import the service from the interface package we just made
from duckie_interfaces.srv import SetColor 

class LEDController(Node):
    def __init__(self):
        super().__init__('led_controller')
        
        # Publisher to Isaac Sim (Twist message)
        self.publisher = self.create_publisher(Twist, '/duckie/led_cmd', 10)
        
        # Service Server
        self.srv = self.create_service(SetColor, '/duckie_led_control', self.led_callback)
        self.get_logger().info("Service Ready: /duckie_led_control")

    def led_callback(self, request, response):
        cmd = Twist()
        req_color = request.color.lower()
        
        # Logic: x=Red, y=Green, z=Blue
        if req_color == 'red':
            cmd.linear.x = 1.0
            self.get_logger().info("Switching to RED")
        elif req_color == 'green':
            cmd.linear.y = 1.0
            self.get_logger().info("Switching to GREEN")
        elif req_color == 'blue':
            cmd.linear.z = 1.0
            self.get_logger().info("Switching to BLUE")
        else:
            self.get_logger().info("Unknown color")
        
        self.publisher.publish(cmd)
        response.success = True
        return response

def main(args=None):
    rclpy.init(args=args)
    node = LEDController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
