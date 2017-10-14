import time
import os
import shutil

releaseDirectory = "release_" + str(time.time())

if not os.path.exists(releaseDirectory):
    os.makedirs(releaseDirectory)

shutil.copytree("./debug/resources", releaseDirectory + "/resources")
shutil.copyfile("./debug/corpgame.exe", releaseDirectory + "/incorporated.exe")

shutil.make_archive(releaseDirectory, 'zip', releaseDirectory)
shutil.rmtree(releaseDirectory)

size = os.path.getsize(releaseDirectory + ".zip")
print("zipped = " + str(round(size / 1024 / 1024, 2)) + " Mb")