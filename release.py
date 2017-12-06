import time
import os
import shutil
import github
import requests
import base64
import re

UPLOAD = True

print("Copying...", end="")

file = open("version.h", 'r+')

contents = file.read()
matches = re.search(r"#define VERSION \"(.*)\"", contents)
oldVersion = matches.group(1)

array = oldVersion.split(".")

major = array[0]
minor = array[1]
build = array[2]

build = int(build) + 1

version = major + "." + minor + "." + str(build)
newContents = contents.replace(oldVersion, version)

file.seek(0)
file.truncate()
file.write(newContents)

binGccDirectory = "gcc-Debug"
binGccName = "corpgame.exe"
binMsvcDirectory = "msvc-Debug"
binMsvcName = "cpp_The_Corp_Game_VC.exe"

if not os.path.exists(binGccDirectory + "/" + binGccName):
    print("\nGcc executable not found... exiting...")
    exit()


timeString = time.strftime("%H-%M-%S_%d-%B", time.localtime())
releaseDirectory = "debug_" + oldVersion

# Copying
if not os.path.exists(releaseDirectory):
    os.makedirs(releaseDirectory + "/gcc(main)")
    os.makedirs(releaseDirectory + "/msvc")

# gcc
if os.path.exists("./" + binGccDirectory + "/" + binGccName):
    shutil.copytree("./resources", releaseDirectory + "/gcc(main)/resources")
    shutil.copyfile("./" + binGccDirectory + "/" + binGccName, releaseDirectory + "/gcc(main)/corpgame.exe")

# msvc
if os.path.exists("./" + binMsvcDirectory + "/" + binMsvcName):
    shutil.copytree("./resources", releaseDirectory + "/msvc/resources")
    shutil.copyfile("./" + binMsvcDirectory + "/" + binMsvcName, releaseDirectory + "/msvc/corpgame.exe")

# manual
shutil.copyfile("./manual.txt", releaseDirectory + "/manual.txt")

print("\r Copying... Done")

# Zipping
print("Zipping...", end="")
shutil.make_archive(releaseDirectory, 'zip', releaseDirectory)
size = os.path.getsize(releaseDirectory + ".zip")
print("\r Zipping... " + str(round(size / 1024 / 1024, 2)) + " Mb")
shutil.rmtree(releaseDirectory)

# Uploading
if UPLOAD:
    print("Uploading...", end="")

    login = "mrAndersen"
    password = "matrixx1s"

    g = github.Github("mrAndersen", "matrixx1s")
    niceTime = time.strftime("%H:%M:%S %d-%B", time.localtime())

    repo = g.get_user().get_repo("cppForestCorporation")

    # New release
    release = repo.create_git_release(tag="debug_" + timeString + "_" + oldVersion, message="Automated release", name=niceTime)
    binaryData = open(releaseDirectory + ".zip", 'rb').read()

    headers = {
        'Authorization': "Basic " + base64.b64encode((login + ":" + password).encode("utf-8")).decode("utf-8").replace('\n', ''),
        'Content-Type': 'application/zip'
    }

    url = release.upload_url.replace("{?name,label}", "") + "?name=" + releaseDirectory + ".zip"
    r = requests.post(url, headers=headers, data=binaryData)

    os.remove(releaseDirectory + ".zip")

    print("\r Uploading... Done\n")
    print("\r" + release.html_url)
    print("\n")