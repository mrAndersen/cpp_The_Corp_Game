import time
import os
import shutil

binDirector = "cmake-build-debug"
releaseDirectory = "release_" + str(time.time())

if not os.path.exists(releaseDirectory):
    os.makedirs(releaseDirectory)

shutil.copytree("./" + binDirector + "/resources", releaseDirectory + "/resources")
shutil.copyfile("./" + binDirector + "/corpgame.exe", releaseDirectory + "/incorporated.exe")

shutil.make_archive(releaseDirectory, 'zip', releaseDirectory)
shutil.rmtree(releaseDirectory)

size = os.path.getsize(releaseDirectory + ".zip")
print("zipped = " + str(round(size / 1024 / 1024, 2)) + " Mb")