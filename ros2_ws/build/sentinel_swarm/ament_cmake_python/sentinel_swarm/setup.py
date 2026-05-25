from setuptools import find_packages
from setuptools import setup

setup(
    name='sentinel_swarm',
    version='0.0.1',
    packages=find_packages(
        include=('sentinel_swarm', 'sentinel_swarm.*')),
)
