# ROS_Exercise

Exercise are carried out in ROS Noetic.

## Publisher and Subscriber

As you can see in the below image i subscribe to /laserscan topic and using float32 ranges message type to get the laser distance and publish to /cmd_vel topic in order to avoid the wall.
code can be [found](src/topics_quiz/src/topics_quiz_node.cpp) here

![mini_project_1](https://user-images.githubusercontent.com/68550704/124513683-a1f9a180-dddb-11eb-8a17-beacd56535eb.gif)
![mini_project_2](https://user-images.githubusercontent.com/68550704/124513689-a45bfb80-dddb-11eb-9426-a1797f5c9da3.gif)
<img width="616" alt="turtle_laser3" src="https://user-images.githubusercontent.com/68550704/124514649-d4a49980-dddd-11eb-9062-94a813356776.png">

## services - Client and server

created a [service server](src/services_quiz/src/bb8_move_custom_service_server.cpp) which would move the robot in square path and a [client](src/services_quiz/src/bb8_move_custom_service_client.cpp) which is using the server.i have also created customservice message for the request and response.

![basic_unit3_variable_square](https://user-images.githubusercontent.com/68550704/124514417-416b6400-dddd-11eb-88ea-f78295002430.png)

## Actions - client and server

Created a [action server](src/action413/src/ms.cpp) so whenever it is called drone will take off and move in a square and then land.

![drone](https://user-images.githubusercontent.com/68550704/124514756-12092700-ddde-11eb-85f0-361b8fc43b62.gif)


