FROM typesafety/typesafety:latest
ENV DEBIAN_FRONTEND noninteractive
MAINTAINER Noritaka Horio <holy.shared.design@gmail.com>
ARG hack_user
ARG hack_group
RUN sudo adduser --disabled-password --gecos "" ${hack_user} && passwd -l ${hack_user}
RUN sudo echo "${hack_user} ALL=(ALL:ALL) NOPASSWD:ALL" >> /etc/sudoers.d/${hack_user}
RUN sudo chmod 440 /etc/sudoers.d/${hack_user} && \
  sudo chown root:root /etc/sudoers.d/${hack_user} && \
  sudo chown -R ${hack_user}:${hack_group} /home/${hack_user}
USER ${hack_user}
ENV HOME /home/${hack_user}
WORKDIR /home/${hack_user}
RUN mkdir project
WORKDIR project
ADD src src
ADD test test
ADD composer.json composer.json
ADD .hhconfig .hhconfig
RUN sudo chown ${hack_user}:${hack_group} composer.json test src
RUN composer install --no-interaction
