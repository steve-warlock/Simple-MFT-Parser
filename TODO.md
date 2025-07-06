# TO DO
    - Create the project structure
        -- we have 3 folders -> src (.cpp files), include (.hpp files), build (the binary location), output (the output of the binary)
    - Create a cmake file
        -- set c++ to 20 
        -- delete existing build folder
        -- create output folder
        -- compile all the files from src + headers
        -- catch existing errors
    - include headers => mft.hpp for the structure of the MFT entry
                      => mft_parser.hpp for the parser logic
                      => utils/logger.hpp for the logging to see everything is going alright
                      => utils/json_converter.hpp for the json convertor
    - src folder => the implementation of all the hpp files
