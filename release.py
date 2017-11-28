import time
import os
import shutil
import argparse
import http.client
import json
import github

parser = argparse.ArgumentParser(description='cpp Deployer')
parser.add_argument('--zip', help='Zip release and put in root directory', action='store_true')
parser.add_argument('--rm', help='Remove folder after creating zip archive', action='store_true')
parser.add_argument('--upload', help="Upload to github", action='store_true')

args = parser.parse_args()

print("Working zip = {}, rm = {}, upload = {}", args.zip, args.rm, args.upload)

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

g = github.Github("mrAndersen", "matrixx1s")
release = g.get_user().get_repo("cpp_The_Corp_Game").create_git_release(tag="early-alpha", message=timeString, name="early-alpha")

print(release.upload_url)

# if args.zip:
#     shutil.make_archive(releaseDirectory, 'zip', releaseDirectory)
#     size = os.path.getsize(releaseDirectory + ".zip")
#     print("zipped = " + str(round(size / 1024 / 1024, 2)) + " Mb")
#
# if args.rm:
#     shutil.rmtree(releaseDirectory)
