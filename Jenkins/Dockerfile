FROM jenkins/jenkins:lts

# Run as root to install system-level packages
USER root

# Update package list
# && install curl (for downloading files)
# && install gnupgs2 (for GPG keys for plugin verif)
# && clean to reduce image size
RUN apt-get update && apt-get install -y --no-install-recommends \
    curl gnupg2 cmake make g++ libboost-all-dev cppcheck clang-tidy \
    python3 python3-pip python3-venv \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Create and activate virtual environment, install packages
RUN python3 -m venv /opt/venv \
    && /opt/venv/bin/pip install --no-cache-dir matplotlib pandas

# Make venv Python the default
ENV PATH="/opt/venv/bin:$PATH"

# Run as non-root user
USER jenkins