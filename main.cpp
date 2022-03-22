#include <spdlog/spdlog.h>
#include "FileReader.h"
#include "GR4J.h"

int main(int argc, char *argv[])
{
    spdlog::info("Starting");
    char *_prec, *_pet, *_disc, *_param, *_out;
    char *_x1, *_x2, *_x3, *_x4, *_s, *_area;
    char* current_arg, *next_arg;

    int _prec_found = 0;
    int _pet_found = 0;
    int _disc_found = 0;
    int _param_found = 0;
    int _out_found = 0;


    int satisfied = 0;

    if (argc == 1)
    {
        spdlog::error(
            "No arguments speficied.\n"
            "Usage:\n"
            "{} --precipitation pathToPrecipitationData "
            "--pet pathToPETData "
            "--discharge pathToDischargeData "
            "--parameters pathToParametersData "
            "--out RsquaredOutputFile\n"
            "\n"
            "\n"
            "If you want to specify the parameters in the command line, use the following arguments:\n"
            "-x1 x1\n"
            "-x2 x2\n"
            "-x3 x3\n"
            "-x4 x4\n"
            "-s s\n"
            "-area area\n"
            "\n"
            "\n"
            "Contents of --precipitation: Each line must correspond to value of that day.\n"
            "\n"
            "Contents of --pet: Each line must correspond to value of that day.\n"
            "\n"
            "Contents of --discharge: Each line must correspond to value of that day.\n"
            "\n"
            "Contents of --out: Outputs the result of Rsquared method.\n"
            "\n"
            "Contents of --param:\nLine\tValue\n1\tX1 Value\n2\tX2 value\n3\tX3 value\n4\tX4 value\n5\tArea of catchment (square km)\n6\tValue of S",
            argv[0]);
        return 1;
    }
    for (size_t i = 1; i < argc; i++)
    {
        current_arg = argv[i];
        next_arg = argv[i + 1];

        if(strcmp(current_arg,"-x1") == 0) {
            if(next_arg != NULL) {
                _x1 = next_arg;
                satisfied++;
            } else {
                spdlog::error("No value specified for -x1");
                return 1;
            }
        }
        if(strcmp(current_arg,"-x2") == 0) {
            if(next_arg != NULL) {
                _x2 = next_arg;
                satisfied++;
            } else {
                spdlog::error("No value specified for -x2");
                return 1;
            }
        }
        if(strcmp(current_arg,"-x3") == 0) {
            if(next_arg != NULL) {
                _x3 = next_arg;
                satisfied++;
            } else {
                spdlog::error("No value specified for -x3");
                return 1;
            }
        }
        if(strcmp(current_arg,"-x4") == 0) {
            if(next_arg != NULL) {
                _x4 = next_arg;
                satisfied++;
            } else {
                spdlog::error("No value specified for -x4");
                return 1;
            }
        }
        if(strcmp(current_arg,"-s") == 0) {
            if(next_arg != NULL) {
                _s = next_arg;
                satisfied++;
            } else {
                spdlog::error("No value specified for -s");
                return 1;
            }
        }
        if(strcmp(current_arg,"-area") == 0) {
            if(next_arg != NULL) {
                _area = next_arg;
                satisfied++;
            } else {
                spdlog::error("No value specified for -area");
                return 1;
            }
        }
        if(strcmp(current_arg,"--precipitation") == 0) {
            if(next_arg != NULL) {
                _prec = next_arg;
                _prec_found = 1;
            } else {
                spdlog::error("No value specified for -precipitation");
                return 1;
            }
        }
        if(strcmp(current_arg,"--pet") == 0) {
            if(next_arg != NULL) {
                _pet = next_arg;
                _pet_found = 1;
            } else {
                spdlog::error("No value specified for -pet");
                return 1;
            }
        }
        if(strcmp(current_arg,"--discharge") == 0) {
            if(next_arg != NULL) {
                _disc = next_arg;
                _disc_found = 1;
            } else {
                spdlog::error("No value specified for -discharge");
                return 1;
            }
        }
        if(strcmp(current_arg,"--parameters") == 0) {
            if(next_arg != NULL) {
                _param = next_arg;
                _param_found = 1;
            } else {
                spdlog::error("No value specified for -parameters");
                return 1;
            }
        }
        if(strcmp(current_arg,"--out") == 0) {
            if(next_arg != NULL) {
                _out = next_arg;
                _out_found = 1;
            } else {
                spdlog::error("No value specified for -out");
                return 1;
            }
        }
    }

    if(satisfied == 6 && _param_found) {
        spdlog::error("Can not set parameters in arguments and specify parameters file at the same time");
        return 1;
    }

    if((satisfied != 6 && satisfied != 0) || !_prec_found || !_pet_found || !_disc_found || !_out_found) {
        spdlog::error("Missing arguments.");
        return 1;
    }

    

    clock_t t, t1 = clock();
    GR4J gr4j;
    {
        FileReader precipitation_data_file(_prec);
        std::vector<long double> prec_data = precipitation_data_file.readFile();

        FileReader pet_data_file(_pet);
        std::vector<long double> pet_data = pet_data_file.readFile();

        FileReader disc_data_file(_disc);
        std::vector<long double> disc_data = disc_data_file.readFile();
        std::vector<long double> param_data;

        if (_param != "")
        {
            FileReader param_data_file(_param);
            param_data = param_data_file.readFile();
        }
        else
        {
            param_data.push_back(std::stold(_x1));
            param_data.push_back(std::stold(_x2));
            param_data.push_back(std::stold(_x3));
            param_data.push_back(std::stold(_x4));
            param_data.push_back(std::stold(_s));
            param_data.push_back(std::stold(_area));
        }

        {
            int prec_data_size = prec_data.size();
            int pet_data_size = pet_data.size();
            int disc_data_size = disc_data.size();
            int param_data_size = param_data.size();
            if (prec_data_size != pet_data_size || prec_data_size != disc_data_size)
            {
                spdlog::error("Data files have different sizes");
                spdlog::info("Precipitation data size: {}", prec_data_size);
                spdlog::info("PET data size: {}", pet_data_size);
                spdlog::info("Discharge data size: {}", disc_data_size);
                spdlog::info("Param data size: {}", param_data_size);
                return 1;
            }
        }

        gr4j.setPr(prec_data);
        std::vector<long double>().swap(prec_data);
        gr4j.setET(pet_data);
        std::vector<long double>().swap(pet_data);
        gr4j.setX1(param_data[0]);
        gr4j.setX2(param_data[1]);
        gr4j.setX3(param_data[2]);
        gr4j.setX4(param_data[3]);
        gr4j.setArea(param_data[4]);
        gr4j.setS(param_data[5]);

        gr4j.setQ(disc_data);
        std::vector<long double>().swap(disc_data);
        gr4j.setRinitial(84);
        gr4j.setup();
    }

    gr4j.calculate();
    gr4j.evaporation_gen();
    gr4j.r_squared();
    {
        FILE *file = fopen(_out, "w");
        fprintf(file, "%.20f", gr4j.getR_squared());
        fclose(file);
    }
    t1 = clock() - t1;
    spdlog::info("Total time taken: {} seconds", ((float)t1) / CLOCKS_PER_SEC);
    spdlog::info("Total time in milliseconds: {}", t1);
}