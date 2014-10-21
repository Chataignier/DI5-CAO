#!/bin/bash

endScriptNormal() {
    qdbus $dbusRef close 2> /dev/null > /dev/null
    exit 0
}

endScriptErrorBox() {
    kdialog --title "$1" --error "$2"
    qdbus $dbusRef close 2> /dev/null > /dev/null
    exit 1
}

endScriptError() {
    qdbus $dbusRef close 2> /dev/null > /dev/null
    exit 1
}



[[ -z $(which kdialog) ]] && "kdialog not found." && exit 1
[[ -z $(which curl) ]] && "curl not found." && exit 1


dbusRef=$(kdialog --title "Preparing an archive for the teacher" --progressbar "Initializing...                                                                                                                                       " 6)
rm -rf archive
mkdir -p archive 


# Step 1 : update source code
qdbus $dbusRef setLabelText "Updating source code..." 2> /dev/null > /dev/null
qdbus $dbusRef Set "" value 1 2> /dev/null > /dev/null
./update.sh || endScriptNormal


# Step 2 : source code compilation
qdbus $dbusRef setLabelText "Compiling sources..." 2> /dev/null > /dev/null
qdbus $dbusRef Set "" value 2 2> /dev/null > /dev/null
make clean all 2>&1 | tee archive/compile.log || endScriptErrorBox "Compiling sources..." "Compilation failed. See archive/compile.log for details" 

# Step 4 : copy sources files
qdbus $dbusRef setLabelText "Copying sources code..." 2> /dev/null > /dev/null
qdbus $dbusRef Set "" value 3 2> /dev/null > /dev/null
cp -r srcstudent archive/

# Step 8 : copy executables
qdbus $dbusRef setLabelText "Copying executables..." 2> /dev/null > /dev/null
qdbus $dbusRef Set "" value 4 2> /dev/null > /dev/null
cp debug/tp archive/tp-debug-$(uname -m)
cp release/tp archive/tp-release-$(uname -m)

# Step 9 : build archive
qdbus $dbusRef setLabelText "Building the archive..." 2> /dev/null > /dev/null
qdbus $dbusRef Set "" value 5 2> /dev/null > /dev/null

archive="archive.tar.gz"
rm $archive 2> /dev/null > /dev/null 
tar -czf $archive archive/ 2>&1 | tee archive.log || endScriptErrorBox "Building the archive..." "An error occurred while building the archive (see archive.log for details)."

kdialog --title "Verify the content of the archive..." --yes-label "All is in the archive" -no-label "Something is missing" --yesno "$(tar -tf $archive)" || ensScriptError

# Step 10 : archive upload
qdbus $dbusRef setLabelText "Uploading the archive..." 2> /dev/null > /dev/null
qdbus $dbusRef Set "" value 6 2> /dev/null > /dev/null


mail=$(kdialog --title "What is your email ?" --inputbox "What is your email ?" "")

kdialog --title "Upload" --yesno "Did you already received a secret id by mail ?" --yes-label "yes" --no-label "no"
if [[ "$?" != "0" ]]; then
    curl "https://storage.projectsforge.org/requestid.php?mail=$mail&project=algograph"
    kdialog -msgbox "You should receive soon your secret id by mail."
fi

id=$(kdialog --title "What is your secret id ?" --inputbox "What is your secret id ?" )

curl -F"operation=upload" -F"file=@$archive" "https://storage.projectsforge.org/upload.php?mail=$mail&project=algograph&id=$id" -o downloaded.tar.gz

diff $archive downloaded.tar.gz && kdialog --title "Upload result" --msgbox "Your archive was uploaded. Bye." || endScriptErrorBox "Error !" "An error occurred while uploading your archive."

endScriptNormal
