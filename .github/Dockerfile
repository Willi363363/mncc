FROM epitechcontent/epitest-docker:latest AS builder
WORKDIR /app/make
COPY . .

RUN make
RUN make clean
RUN make fclean
# Cleaning and testing basic executable

CMD make re ; ls -l mncc