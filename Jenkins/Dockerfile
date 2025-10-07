FROM jenkins/jenkins:lts

# Run as root to install system-level packages
USER root

# Update package list
# && install curl (for downloading files)
# && install gnupgs2 (for GPG keys for plugin verif)
# && clean to reduce image size
RUN apt-get update && apt-get install -y --no-install-recommends \
curl gnupg2 cmake make g++ libboost-all-dev cppcheck clang-tidy \
&& apt-get clean && rm -rf /var/lib/apt/lists/*


# Run as non-root user
USER jenkins

# Disables initial setup wizard
# ENV JAVA_OPTS="-Djenkins.install.runSetupWizard=false"

# Copies list of desired plugins for Jenkins to initialize on run
# COPY plugins.txt /usr/share/jenkins/ref/plugins.txt

# Use Jenkin's plugin CLI to install all plugins to ensure they're available
# before Jenkins starts
# RUN jenkins-plugin-cli --plugin-file /usr/share/jenkins/ref/plugins.txt
