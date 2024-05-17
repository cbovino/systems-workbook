FROM amd64/ubuntu
RUN apt update
RUN yes | apt-get install build-essential
RUN yes | apt-get install gcc-multilib

CMD tail -f /dev/null