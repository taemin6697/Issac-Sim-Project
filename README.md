# **Isaac Sim 기반 Duckiebot 자율주행 시뮬레이션 프로젝트**

**과목:** 로보틱스와 인공지능 기말 과제

**환경:** NVIDIA Isaac Sim (Windows) \+ ROS2 Humble (WSL2 Ubuntu 22.04)

**패키지명:** duckie\_control

## **1\. 프로젝트 개요**

본 프로젝트는 NVIDIA Isaac Sim 환경에서 Duckiebot을 모델링하고, ROS2 Bridge를 통해 제어 및 영상처리를 수행하는 자율주행 시스템을 구축하는 것을 목표로 합니다.  
WSL2(ROS2)와 Windows(Isaac Sim) 간의 통신을 통해 다음 기능들을 구현했습니다:

1. **LED 제어:** 커스텀 ROS2 Service를 이용한 로봇 색상 변경  
2. **모터 제어:** Twist 메시지를 이용한 차동 구동(Differential Drive) 제어  
3. **카메라 스트리밍:** Isaac Sim 내 RGB 카메라 영상 ROS 토픽 송출  
4. **자율주행 (Visual Servoing):** OpenCV 기반 Red Cube 인식 및 추종 주행

## **2\. 시스템 요구사항 (Prerequisites)**

* **OS:** Windows 10/ (Isaac Sim 4.0 이상) & WSL2 (Ubuntu 22.04)  
* **ROS2 Version:** Humble Hawksbill  
* **Python Dependencies:** opencv-python, cv\_bridge  
* **Isaac Sim Setup:**  
  * Action Graph 구성 필수 (ROS2 Bridge, Differential Controller, Camera Helper 등)  
  * Dome Light 추가 권장 (영상처리 인식률 향상)

## **3\. 설치 및 빌드 방법 (Installation)**

ROS2 워크스페이스(\~/ros2\_ws)를 기준으로 설명합니다.

\# 1\. 소스 코드 위치 확인 (패키지 폴더가 src 안에 있어야 함)  
cd \~/ros2\_ws/src

\# 2\. 의존성 설치  
cd \~/ros2\_ws  
rosdep install \-i \--from-path src \--rosdistro humble \-y

\# 3\. 패키지 빌드  
colcon build \--packages-select duckie\_control

\# 4\. 환경 설정 적용  
source install/setup.bash

** 환경에 따라 일부 실행이 안될수도 있습니다. **

## **4\. 실행 및 기능 시연 (Demo Instructions)**

**사전 준비:**

1. Isaac Sim 실행 및 Duckiebot .usd 파일 로드  
2. **Play (▶)** 버튼 클릭 (필수)

### **기능 1: LED 제어 서비스 (LED Service)**

요구사항 (2)에 해당하며, 색상 문자열(red, blue, green)을 요청하여 로봇 상태를 변경합니다.

**1\. 서비스 서버 실행 (터미널 1\)**

ros2 run duckie\_control led\_service

**2\. 서비스 요청 (터미널 2 \- 새 창 열기)**

\# 빨간색으로 변경 요청  
ros2 service call /duckie\_led\_control duckie\_interfaces/srv/SetColor "{color: 'red'}"

\# 파란색으로 변경 요청  
ros2 service call /duckie\_led\_control duckie\_interfaces/srv/SetColor "{color: 'blue'}"

\# 초록색으로 변경 요청  
ros2 service call /duckie\_led\_control duckie\_interfaces/srv/SetColor "{color: 'blue'}"

### **기능 2: ROS 기반 모터 제어 (Motor Control)**

요구사항 (3)에 해당하며, High-level(cmd\_vel) 명령을 전송하여 로봇을 움직입니다.

**저수준 모터제어** 

직진

ros2 topic pub \--once /duckie/wheel\_left\_cmd geometry\_msgs/msg/Twist "{linear: {x: 5.0}}"

ros2 topic pub \--once /duckie/wheel\_right\_cmd geometry\_msgs/msg/Twist "{linear: {x: 5.0}}"

제자리 우회전

ros2 topic pub \--once /duckie/wheel\_left\_cmd geometry\_msgs/msg/Twist "{linear: {x: 5.0}}"

ros2 topic pub \--once /duckie/wheel\_right\_cmd geometry\_msgs/msg/Twist "{linear: {x: 0.0}}"

**고수준 모터제어**

**1\. 정지 (Stop \- 급정지)**

ros2 topic pub \--once /duckie/cmd\_vel geometry\_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}"

**2\. 전진 (Move Forward)**

ros2 topic pub \--once /duckie/cmd\_vel geometry\_msgs/msg/Twist "{linear: {x: 0.3}, angular: {z: 0.0}}"

**3\. 회전 (Turn Left/Right)**

\# 좌회전 (제자리)  
ros2 topic pub \--once /duckie/cmd\_vel geometry\_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 1.0}}"

\# 우회전 (제자리)  
ros2 topic pub \--once /duckie/cmd\_vel geometry\_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: \-1.0}}"

### **기능 3: 카메라 영상 확인 (Camera Stream)**

**1\. 토픽 리스트 확인**

ros2 topic list  
\# 출력 확인: /duckie/camera/image\_raw, /duckie/camera/image\_raw/compressed

**2\. 영상 시각화 (RQT)**

rqt, rviz2  
\# 메뉴: Plugins \-\> Visualization \-\> Image View  
\# Topic 선택: /duckie/camera/image\_raw

### **기능 4: 자율주행 \- Red Cube 추종 (Visual Servoing)**

**1\. 자율주행 노드 실행**

ros2 run duckie\_control visual\_servoing

**2\. 동작 원리 (Algorithm)**

* **Image Processing:** RGB \-\> HSV 변환 \-\> Red Color Masking \-\> Contour 추출.  
* **Control Logic:**  
  * **Rotation:** 화면 중앙(center\_x)과 객체 중심(cx)의 오차(err\_x)에 비례하여 회전 (P-Control).  
  * **Linear:** 객체의 면적(area)이 작으면(멀면) 전진, 일정 크기 이상이면(가까우면) 정지.

## **5\. 프로젝트 파일 구조 (File Structure)**

duckie\_control/  
├── package.xml             \# 패키지 의존성 및 메타데이터  
├── CMakeLists.txt          \# 빌드 설정  
├── setup.py                \# 파이썬 엔트리 포인트 설정  
├── srv/  
│   └── SetColor.srv        \# \[Custom Message\] string color \-\> bool success  
└── duckie\_control/  
    ├── \_\_init\_\_.py  
    ├── led\_service.py      \# \[Node\] LED 제어 서비스 서버  
    └── visual\_servoing.py  \# \[Node\] 영상처리 및 자율주행 제어  
