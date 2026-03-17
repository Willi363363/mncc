FROM epitechcontent/epitest-docker:latest AS builder
WORKDIR /app/make
COPY . .

RUN make
RUN make clean
RUN make fclean
RUN make re
RUN make unit_tests
RUN make tests_clean
RUN make tests_re

# Cleaning and testing basic executable

CMD make re ; ls -l mncc