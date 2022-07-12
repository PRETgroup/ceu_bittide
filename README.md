Requires the Ceu language: https://github.com/ceu-lang/ceu

I have been running this on Ubuntu 20.04 under WSL without any major dramas, after resolving various dependencies through apt. You will only be able to run many of the graphical Ceu examples if you forward your xserver and pulseaudio output, but that should not be necessary for running this simulator.

***Building Using Docker on MacOS***

The quickest way to get Ceu working on MacOS (or Windows) is to deploy the provided docker container in the ceu language repo. To do so, first install docker using you method of choice:

`brew install --cask docker`

Launch docker from your applications menu to complete first-time setup. In your terminal, navigate to the etc/ceu-docker folder in your ceu repo.
By typing the following command you can download and deploy a new docker container containing a copy of Ubuntu with the ceu project installed:
`docker run -it ceulang/ceu`

After the docker image has been succesfully installed, you will find yourself in a command prompt within the deployed Ubuntu image. You will also see an image has been created with an automatically assigned name in the docker dashboard. From within this command prompt, you can clone this git repository onto the virtual machine.

Finally, we need to add the location of Ceu to our system variables so that our simulator can find the relevant files.
`echo 'export CEU_DIR=/ceu/' >> ~/.bashrc`

`source ~/.bashrc`

Hopefully, you should now be able to make the bittide simulator using `./make_all.sh` and `./make_all.sh run`

When you wish to open the docker image again, simply run `docker start -i <container name>` from your terminal.

The easiest way to modify files within the docker image is through use of the vscode 'Remote - Containers' extension which will let you attach your editor to any running docker container. I recommend you install the vscode extension that can be found in the ceu repo for syntax highlighting. 


