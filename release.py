import time
import os
import shutil
import github
import requests
import base64

print("Copying...", end="")

binGccDirector = "cmake-build-debug"
binMsvcDirectory = "Debug"

timeString = time.strftime("%H-%M-%S_%d-%B", time.localtime())
releaseDirectory = "release_" + timeString

# Copying

if not os.path.exists(releaseDirectory):
    os.makedirs(releaseDirectory + "/gcc")
    os.makedirs(releaseDirectory + "/msvc")

# gcc
shutil.copytree("./resources", releaseDirectory + "/gcc/resources")
shutil.copyfile("./" + binGccDirector + "/corpgame.exe", releaseDirectory + "/gcc/corpgame.exe")

# msvc
shutil.copytree("./resources", releaseDirectory + "/msvc/resources")
shutil.copyfile("./" + binMsvcDirectory + "/cpp_The_Corp_Game_VC.exe", releaseDirectory + "/msvc/corpgame.exe")

# manual
shutil.copyfile("./manual.txt", releaseDirectory + "/manual.txt")

print("\r Copying... Done")

# Zipping
print("Zipping...", end="")
shutil.make_archive(releaseDirectory, 'zip', releaseDirectory)
size = os.path.getsize(releaseDirectory + ".zip")
print("\r Zipping... " + str(round(size / 1024 / 1024, 2)) + " Mb")

# Uploading
shutil.rmtree(releaseDirectory)


print("Uploading...", end="")

login = "mrAndersen"
password = "matrixx1s"

g = github.Github("mrAndersen", "matrixx1s")
niceTime = time.strftime("%H:%M:%S %d-%B", time.localtime())
release = g.get_user().get_repo("cppForestCorporation").create_git_release(tag="early-alpha-" + timeString, message="Automated release", name=niceTime)

binaryData = open(releaseDirectory + ".zip", 'rb').read()

headers = {
    'Authorization': "Basic " + base64.b64encode((login + ":" + password).encode("utf-8")).decode("utf-8").replace('\n', ''),
    'Content-Type': 'application/zip'
}

url = release.upload_url.replace("{?name,label}", "") + "?name=" + releaseDirectory + ".zip"
r = requests.post(url, headers=headers, data=binaryData)

shutil.rmtree(releaseDirectory + ".zip")

print("\r Uploading... Done\n")
print("\r" + release.html_url)
print("\n")