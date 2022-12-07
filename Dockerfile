FROM epitechcontent/epitest-docker:devel

COPY Asset/ /app/bombercraft/Asset/
COPY include/ /app/bombercraft/include/
COPY lib/ /app/bombercraft/lib/
COPY src/ /app/bombercraft/src/
COPY CMakeLists.txt /app/bombercraft/

WORKDIR /app/bombercraft/build
RUN cmake ..
RUN make
WORKDIR /app/bombercraft

CMD mv ./bomberman /app/shared