include(Testing)

add_googletest(
    TARGET test_soundex
    SOURCE_FILES TestSoundex.cpp
    LIBRARIES soundex
)