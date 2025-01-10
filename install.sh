
#!/bin/bash
sudo apt-get install -y libsfml-dev

git clone git@github.com:nlohmann/json.git

sudo cp -r ./json/include/* /usr/include

sudo rm -rf ./json