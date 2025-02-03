import face_recognition
import cv2
from ament_index_python.packages import get_package_share_directory #获取功能包share的绝对路径
import os

def main():
    default_image_path = os.path.join(get_package_share_directory('demo_python_pkg'), 'resource', 'default.jpg')
    print(default_image_path)

    image = cv2.imread(default_image_path)
    #检测人脸
    face_locations = face_recognition.face_locations(image,number_of_times_to_upsample=1,model='hog')
    #绘制人脸边框
    for (top, right, bottom, left) in face_locations:
        cv2.rectangle(image, (left, top), (right, bottom), (0, 0, 255), 2)
    cv2.imshow('image', image)
    cv2.waitKey(0)


if __name__ == '__main__':
    main()