# Use an official gcc image as a base
FROM gcc:latest

# Set the working directory in the container
WORKDIR /app

# Copy the source files to the container
COPY . .

# Compile the project
RUN make

# Set entrypoint to bash
CMD ["/bin/bash"]
