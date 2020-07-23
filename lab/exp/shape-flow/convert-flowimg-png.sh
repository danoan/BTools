BASE_PATH="$(realpath "$1")"
CURR_PATH="$PWD"

TEMP="$CURR_PATH/.temp-convert"
rm "$TEMP"
find "$BASE_PATH" -name "input-data.txt" -print | xargs dirname >> "$TEMP"
cat "$TEMP" | xargs -I{} mogrify -format png {}/*.pgm
cat "$TEMP" | xargs -I@ bash -c 'rm @/*.pgm'
rm "$TEMP"




