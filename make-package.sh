VERSION=$(<.version)
echo "$VERSION"
ALIAS=json-shader/latest
TARGET=json-shader/$VERSION
NS=jeffw387/testing
conan create . $NS --build=missing --settings="cppstd=17"
conan alias $ALIAS@$NS $TARGET@$NS
conan upload "$TARGET@$NS" -r jeffw --all --confirm
conan upload "$ALIAS@$NS" -r jeffw --all --confirm