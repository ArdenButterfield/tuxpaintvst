# Tux VST

Okay, this is kind of a silly idea, but I got it in my head, and I think it could be pretty cool: A VST plugin that can run inside the DAW, and that is a (as close as possible to) fully-functional Tux Paint program. It could be really cool to even expand Tux Paint to have audio input/output functionality.

I have basically no idea how this would work under the hood. But let's find out.

## Motivation

I would learn some cool skills about C and C++ and about how the VST API actually works. And it would be cool and funny and I could show it to people. The usual.

## Building Tux Paint from Source Code

Tux Paint is open source. We download the source from the Tux Paint website: https://tuxpaint.org/download/source/.

`wget https://sourceforge.net/projects/tuxpaint/files/tuxpaint/0.9.31/tuxpaint-0.9.31.tar.gz/download`

Next we need to install the dependencies, roughly following the instructions in INSTALL.txt, but really just chasing the errors that the IDE gives us.

```sh
sudo apt-get install libsdl2-2.0-0
sudo apt-get install libsdl2-dev
```

we also need `libimagequant`, following the instructions at https://github.com/ImageOptim/libimagequant and running `sudo make install`.

SDL2_Pango

```
    $ git clone https://github.com/markuskimius/SDL2_Pango
    $ cd SDL2_Pango
    $ ./configure && make && make install
```