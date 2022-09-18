---
title: "Docker Cheat sheet"
excerpt: "Very brief Docker Intro and Cheat sheet"
tags:
  - docker
categories:
  - tools
---

## Getting Started

Docker is really well documented, see

* [Official Get Started](https://docs.docker.com/get-started/)
* [An other step by step tutorial](https://www.howtoforge.com/tutorial/how-to-create-docker-images-with-dockerfile/)
* [and the offical DOCs page](https://docs.docker.com/)

## Terms/Concept

* Image, executable package
  * [tons of community images are available](https://hub.docker.com/search?q=&type=image)
* Container, a running image or an instance
* Dockerfile, the "plan" to build an image

## Dockerfile Example

```bash
# our base image
FROM ubuntu:16.04 

# make Directories
RUN mkdir -p /mnt/log/

# install some stuff, I never wanna miss the loco
RUN apt install -y sl

# copy files/folders to image
COPY ./local/folder /image/folder  

# some more commands, set files execuatble
RUN chmod +x /image/folder/*

# tell the port number the container should expose
# ssh
EXPOSE 22 
# http
EXPOSE 80 

# run the application
CMD /image/folder/myStartApp.sh
```

## Cheat Sheet

```bash
# complete reference at 
# https://docs.docker.com/engine/reference/commandline/docker/

docker build -t <IMAGE_NAME> <FOLDER>            # builds image from docker file, FOLDER contains dockerfile and app-specific files
   
docker image ls                                  # lists all images (built, and downloaded)

docker run <IMAGE_NAME>                          # runs an image (and creates a container)

docker run <IMAGE_NAME <CMD>                     # runs an image and a single Command

docker run -it <IMAGE_NAME bash                  # runs interactive shell

docker start <ID>                                # starts an existing container      

docker container ls                              # lists all running containers
   
docker exec -it <ID> <CMD>                       # runs a command on a running container, ID from container ls
                                                 # use /bin/bash to open a shell

docker stop <ID>                                 # stops container, ID from container ls

docker rm <ID>                                   # remove container

docker stop $(docker ps -a -q)                   # bash only, stop all containers

docker cp <ID>:/container/path /host/path/target # copies files from container 

docker tag image username/repository:tag         # tags an image

docker images -f "dangling=true" -q              # list untagged images

docker rmi -f <IMAGE>                            # remove image

docker inspect <ID>                              # get Details (eg IP)

docker run -p 8080:80 <IMAGE_NAME>               # forward incoming connections (8080) to container port 80

docker container ls -a --filter status=exited    # show stopped container

docker system prune                              # remove unused data

docker volume create <VOL>                       # create Volume

docker volume ls                                 # show volumes

docker volume inspect <VOL>                      # inpect

docker run --mount type=bind,source=<VOL>,target=/app <IMAGE> <CMD> # mount volume
```
