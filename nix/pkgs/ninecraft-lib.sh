set -e
# set -x

installVersion() {
	if [[ -n "$gameDir" && -r "$gameDir" ]]; then
		VERSION=$1
        ARCH=$2
		VERSION_PATH=$(readlink -f $VERSION)
		
		pushd "$gameDir"
		rm -rf assets res lib

		if [[ -d "$VERSION_PATH" ]]; then
			cp -r "$VERSION_PATH"/{assets,lib,res} "$gameDir"
		else

			if [[ $VERSION =~ ^https?:\/\/ ]]; then
				URL=$VERSION
			else
			if [[ -z "$ARCH" ]]; then

				URL="https://archive.org/download/MCPEAlpha/PE-a${VERSION}.apk"
				else
				URL="https://archive.org/download/MCPEAlpha/PE-a${VERSION}-${ARCH}.apk"
				fi
			fi

			if [[ -f "$VERSION_PATH" ]];  then
				APK=$VERSION_PATH
			else
				echo "Downloading Minecraft PE from $URL..."
				curl -L --output mcpe.apk "$URL"
				APK=$(pwd)/mcpe.apk
			fi
		
			echo "Extracting APK $APK..."
			ninecraft-extract "$APK"
		fi

		
		chmod -R u+w "$gameDir"/{assets,lib,res}

		pwd
		ls	
	fi
}