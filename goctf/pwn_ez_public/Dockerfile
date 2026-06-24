FROM ubuntu:26.04@sha256:5e275723f82c67e387ba9e3c24baa0abdcb268917f276a0561c97bef9450d0b4

RUN apt-get update
RUN apt-get install -y socat

RUN mkdir /app
WORKDIR /app

COPY chall .
COPY run.sh .
COPY flag.txt .
RUN chmod 555 chall
RUN chmod 555 run.sh
RUN chmod 444 flag.txt
RUN mv flag.txt flag-$(md5sum flag.txt | awk '{print $1}').txt

RUN useradd pwn
USER pwn

EXPOSE 6700
CMD ["./run.sh"]
