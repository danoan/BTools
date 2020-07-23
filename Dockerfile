#Use an official Python runtime as a parent image
FROM danoan/dipacus:env

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

RUN chmod +x /app/scripts/*
RUN /app/scripts/build-btools.sh
