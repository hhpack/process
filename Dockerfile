FROM holyshared/typesafety:latest
ENV DEBIAN_FRONTEND noninteractive
LABEL maintainer "Noritaka Horio <holy.shared.design@gmail.com>"
ARG hack_user
ARG hack_group
ARG GITHUB_CREDENTIALS_TOKEN
RUN adduser --disabled-password --gecos "" ${hack_user} && passwd -l ${hack_user}
USER ${hack_user}
ENV HOME /home/${hack_user}
WORKDIR /home/${hack_user}
RUN mkdir project
WORKDIR project
ADD src src
ADD test test
ADD example example
ADD composer.json composer.json
ADD hh_autoload.json hh_autoload.json
ADD .hhconfig .hhconfig
RUN composer install --no-interaction
