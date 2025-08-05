FROM debian@sha256:2424c1850714a4d94666ec928e24d86de958646737b1d113f5b2207be44d37d8 \
AS base

RUN apt-get update && apt-get install -y build-essential \
 && apt-get install -y libncurses5-dev \
 && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /home/2048
COPY . .

RUN make

CMD ["./2048"]
