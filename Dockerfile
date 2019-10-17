FROM alpine:3.10.2 AS base
MAINTAINER Patrick Kuijvenhoven <patrick.kuijvenhoven@gmail.com>

FROM base AS builder

RUN apk --no-cache add libusb-dev gcc g++ make
RUN mkdir -p /usr/local/src/mochad/
WORKDIR /usr/local/src/mochad/
COPY . .
RUN ./configure && make && make install 

FROM builder AS prod

COPY --from=builder /usr/local/bin/mochad /usr/local/bin/mochad

EXPOSE 1099

CMD ["/usr/local/bin/mochad", "-d"]
