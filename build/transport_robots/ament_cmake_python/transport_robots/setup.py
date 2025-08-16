from setuptools import find_packages
from setuptools import setup

setup(
    name='transport_robots',
    version='0.0.0',
    packages=find_packages(
        include=('transport_robots', 'transport_robots.*')),
)
