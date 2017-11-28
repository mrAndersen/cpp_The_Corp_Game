import time
import os
import shutil
import argparse
import http.client
import json
import github
import requests
import base64

# parser = argparse.ArgumentParser(description='cpp Deployer')
# parser.add_argument('--zip', help='Zip release and put in root directory', action='store_true')
# parser.add_argument('--rm', help='Remove folder after creating zip archive', action='store_true')
# parser.add_argument('--upload', help="Upload to github", action='store_true')

# args = parser.parse_args()
# print("Working zip = {}, rm = {}, upload = {}", args.zip, args.rm, args.upload)

print("Copying...", end="")

binGccDirector = "cmake-build-debug"
binMsvcDirectory = "Debug"

timeString = time.strftime("%H-%M-%S_%d-%B", time.localtime())
releaseDirectory = "release_" + timeString

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

if True:
    print("Zipping...", end="")
    shutil.make_archive(releaseDirectory, 'zip', releaseDirectory)
    size = os.path.getsize(releaseDirectory + ".zip")
    print("\r Zipping... " + str(round(size / 1024 / 1024, 2)) + " Mb")

if True:
    shutil.rmtree(releaseDirectory)

if True:
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