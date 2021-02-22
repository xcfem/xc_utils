scriptName=`basename "$0"`
echo "Work in progress; use with CAUTION."

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
packages_build="\
    git         \
    cmake       \
    g++         \
    gfortran    \
    libboost-all-dev"
apt-get install -y $packages_build

packages_lib="\
    libcgal-dev               \
    libcgal-qt5-dev           \
    libglib2.0-dev            \
    libgmp3-dev               \
    libgtk2.0-dev             \
    libgtkgl2.0-dev           \
    libgtkglextmm-x11-1.2-dev \
    libgtkmm-2.4-dev          \
    libgtkglext1-dev          \
    libgts-bin                \
    libgts-dev                \
    libmpfr-dev               \
    libmysql++-dev            \
    libplot-dev               \
    libsqlite3-dev            \
    libvtk7-dev               \
    libx11-dev"
sudo apt-get install -y $packages_lib

packages_dev="\
    python3-dev          \
    cimg-dev"
sudo apt-get install -y $packages_dev

packages_python="\
    python3-vtk7         \
    python3-numpy        \
    python3-scipy        \
    python3-sympy        \
    python3-matplotlib   \
    python3-pandas       \
    python3-sklearn      \
    python3-pip"
sudo apt-get install -y $packages_python

packages_div="\
    gnuplot \
    python3-pip \
    bc"
# bc is needed by xc_utils verification tests
sudo apt-get install -y $packages_div

# free disk space by cleaning install files
sudo apt-get clean

apt-get install  

# cairo installation. 
sudo -H pip3 install pycairo
sudo -H pip3 install ezdxf

