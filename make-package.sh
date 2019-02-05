# pass package version as argument 1
ALIAS=json-shader/latest
TARGET=json-shader/$1
NS=jeffw387/testing
conan create . $NS
conan alias $ALIAS@$NS $TARGET@$NS
conan upload "$TARGET@$NS" -r jeffw --all --confirm
conan upload "$ALIAS@$NS" -r jeffw --all --confirm