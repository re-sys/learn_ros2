from setuptools import find_packages, setup

package_name = 'demo_python_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/resource', ['resource/default.jpg']),
        ('share/' + package_name + '/launch', ['launch/demo.launch.py']),
        ('share/'+package_name +"/config", ['config/waypoints.yaml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='wufy',
    maintainer_email='2565896577@qq.com',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        'demo_python_node = demo_python_pkg.learn_face_default:main',
        'face_detect_node = demo_python_pkg.face_detect_node:main',
        'face_detect_client = demo_python_pkg.face_detect_client:main'
        ],
    },
)
