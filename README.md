https://github.com/user-attachments/assets/ff39cdf7-fe1c-4524-bfcc-12ecbc1f7b37
📷 Demo
🚗 Intelligent Road Sign Recognition System for Automated Vehicle Navigation
📌 Project Overview

This project presents an AI-based Road Sign Recognition System designed to assist automated vehicle navigation. The system uses a Convolutional Neural Network (CNN) to identify traffic signs from input images and translate them into vehicle control commands.

A PyQt-based graphical interface allows users to provide traffic sign images, which are processed by the trained model. The predicted sign is then converted into commands and transmitted via Wi-Fi to an ESP8266 module, enabling the vehicle to perform corresponding actions such as stopping, turning, or speed control.

This prototype demonstrates the integration of Artificial Intelligence, Computer Vision, and IoT for intelligent transportation systems.

🎯 Objectives

Develop an AI-based traffic sign recognition model.

Integrate computer vision with vehicle control.

Demonstrate automated navigation decisions using traffic signs.

Build a low-cost prototype that can be extended to real-time autonomous vehicles.

⚙️ Key Features

CNN-based traffic sign classification

Recognition of 43 traffic sign classes

PyQt5 graphical user interface for image input

Real-time prediction and display

Wireless command transmission using ESP8266

Automated vehicle response to recognized signs

🧠 Technologies Used

Python

PyQt5

TensorFlow / Keras

NumPy

PIL (Python Imaging Library)

Scikit-learn

Matplotlib

ESP8266 (NodeMCU)

Wi-Fi Communication

🔧 Hardware Components

Laptop / PC (for AI processing and GUI)

ESP8266 (NodeMCU) Wi-Fi module

Motor Driver (L298N / L293D)

DC Motors

Robot Chassis with Wheels

Rechargeable Battery

Jumper Wires

Note: In this prototype, traffic sign images are provided manually through the GUI instead of using a camera.

🖥️ Software Workflow

User loads a traffic sign image through the PyQt GUI.

The image is resized and preprocessed.

The trained CNN model predicts the traffic sign class.

The predicted sign is displayed on the interface.

A corresponding command is sent to the ESP8266 via HTTP.

The vehicle performs the required action.

🔁 System Flow

Input Image → Image Preprocessing → CNN Classification → Sign Recognition → Command Generation → ESP8266 → Vehicle Action

🚀 Future Improvements

Integrate live camera-based traffic sign detection

Implement real-time video processing using OpenCV

Deploy AI model on Raspberry Pi or embedded systems

Add lane detection and obstacle avoidance

Develop a fully autonomous driverless vehicle system

📊 Dataset

The model is trained on a Traffic Sign Recognition Dataset containing 43 classes, resized to 30×30 RGB images.
