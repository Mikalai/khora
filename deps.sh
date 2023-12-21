if [ -z "$1" ]; then
    echo "You must pass the path to vcpkg as the first parameter"
    exit 1
fi

vcpkg_path="$1"

"$vcpkg_path" install boost glm fmt gtest magic-enum --triplet=x64-linux --recurse

