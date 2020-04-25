scriptName=`basename "$0"`
# Must run as root so that we can shutdown backuppc and mount drives
if [ $(whoami) != "root" ]; then
    echo "You must run this script as root."
    echo "Use 'sudo sh $scriptName' and enter the password when prompted."
    exit 1
fi

# print information about non-free packages
echo "Some packages are in the \"contrib\" and \"non-free\" areas of the Debian distribution so these areas should be included in the sources.list file before running this script."

# verify that the user wants to continue, but do not verify if a parameter DoNotAsk was given with script start
if [ $1 != "DoNotAsk" ]; then
    read -p "Continue (y/n)?" REPLY
    if [ $REPLY != "y" ]; then
        echo "Exiting..."
        exit 1
    fi
fi

# packages installed by debian package manager apt-get
# tested on Debian Stretch
packages_build="\
    git         \
    cmake       \
    g++         \
    gfortran    \
    libboost-all-dev"
apt-get install -y $packages_build

packages_lib="\
    libcgal-dev                 \
    libglib2.0-dev              \
    libgmp3-dev                 \
    libgtk2.0-dev               \
    libgtkgl2.0-dev             \
    libgtkglextmm-x11-1.2-dev   \
    libgtkmm-2.4-dev            \
    libgtkglext1-dev            \
    libX11-dev                  \
    libgts-bin                  \
    libgts-dev                  \
    libmpfr-dev                 \
    libmysql++-dev              \
    libplot-dev                 \
    libsqlite3-dev              \
    libvtk6-dev                 \
    libmetis-dev"
apt-get install -y $packages_lib

packages_dev="\
    python-dev          \
    cimg-dev"
apt-get install -y $packages_dev

packages_python="\
    python-vtk6         \
    python-numpy        \
    python-scipy        \
    python-sympy        \
    python-matplotlib   \
    python-pandas       \
    python-sklearn      \
    python-dev          \
    python-pip"
apt-get install -y $packages_python

packages_div="\
    gnuplot \
    bc"
# bc is needed by xc_utils verification tests
apt-get install -y $packages_div

# free disk space by cleaning install files
apt-get clean

# cairo installation. 
sudo -H pip install pycairo


