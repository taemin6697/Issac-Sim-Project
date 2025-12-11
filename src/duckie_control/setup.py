from setuptools import find_packages, setup

package_name = 'duckie_control'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='tm0118',
    maintainer_email='tm0118@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'led_service = duckie_control.duckie_led_service:main',
            'visual_servoing = duckie_control.visual_servoing:main',
        ],
    },
)
