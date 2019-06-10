# SLAM_Wheel-E
Este es un proyecto en el cual se busca realizar una comparativa de diferentes técnicas de SLAM empleando un robot movil diferencial tipo Rover.

![alt text](/docs/latex/images/slam/bag1_rtabmapbonito.jpg "RTABmap")

![alt text](/docs/latex/images/slam/bag3_orb_map.jpg "ORB")

# Wheel-E 
![alt text](/docs/latex/images/wheele_real.jpg "wheele")

Un desarrollo en profundidad del proyecto se encuentra en la carpeta docs.

# DEPENDENCIAS
## Uso de lod gpio de la RPi
Se hace uso de la libreria pigpio:(http://abyz.me.uk/rpi/pigpio/download.html)

```
wget abyz.me.uk/rpi/pigpio/pigpio.tar
tar xf pigpio.tar
cd PIGPIO
make
sudo make install
```

## Comunicación Serial RPi-Arduino
Se hará uso de la librería de Python:

https://github.com/harmsm/PyCmdMessenger

Destacar que se emplará python2.7 y no python3.

## Comunicación multimaster(https://wiki.ros.org/multimaster_fkie)
Para comunicar la RPi y el PC, es necesario tener instalado el siguiente paquete:

```
sudo apt install ros-kinetic-multimaster-fkie
sudo apt install ros-kinetic-multimaster-launch
```

## Drivers Kinect v1 (RGB-D Camera)
Se emplearán tanto los driver necesarios para leer la IMU de la cámara y mover su motor cómo los que permiten que se pueda correr la cámara.

 - Drivers Cámara principales
```
sudo apt install ros-kinetic-freenect-stack<
```

 - Driver IMU y motor de la cámara(https://wiki.ros.org/kinect_aux)
```
sudo apt-get install libusb-1.0-0 libusb-1.0-0-dev
```
```
cd ~/catkin_ws/src
git clone https://github.com/muhrix/kinect_aux.git -b indigo
cd ~/catkin_ws
catkin_make
```

## RTAB-Map SLAM
Se deberan tener instalados los siguientes paquetes de ros y sus respectivas dependencias:
```
sudo apt-get install ros-kinetic-rtabmap-ros
sudo apt-get install ros-kinetic-octomap-*

```

## ORB-SLAM2
Se enlaza directamente al repositorio original.
https://github.com/appliedAI-Initiative/orb_slam_2_ros

