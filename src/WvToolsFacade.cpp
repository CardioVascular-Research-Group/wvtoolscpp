//
// Created by rliu14 on 6/16/16.
//

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "WvToolsFacade.h"
#include "io/DataWriter.h"
#include "io/PhysionetWriter.h"
#include "util/ChecksumCalculator.h"
#include "io/QrsOnsetReader.h"
#include "util/FeatureCalculator.h"
#include "util/SvmParams.h"
#include "util/QualityChecker.h"

using std::vector;

void WvToolsFacade::write_data(std::ostream &os, const std::string &prefix, const bool &scaled, const bool &headers,
                               const bool &timestamps) {
    try {
        InfoReader info_reader(prefix);
        WvReader wv_reader(prefix);

        DataWriter writer(os);
        writer.write(info_reader, wv_reader, headers, timestamps, scaled);
        wv_reader.close();
    } catch (IOException& e) {
        cerr << e.get_message() << endl;
    }
}

void WvToolsFacade::write_physionet(std::ostream &os, const std::string &prefix) {
    try {
        InfoReader info_reader(prefix);
        WvReader wv_reader(prefix);

        PhysionetWriter writer(os);
        writer.write(info_reader, wv_reader, prefix);
        wv_reader.close();
    } catch (IOException& e) {
        cerr << e.get_message() << endl;
    }
}


void WvToolsFacade::write_checksums(std::ostream &os, const std::string &prefix) {
    try {
        InfoReader info_reader(prefix);
        WvReader wv_reader(prefix);

        ChecksumCalculator calculator(info_reader.num_channels());
        while (wv_reader.has_next()) {
            calculator.add(wv_reader.next());
        }
        wv_reader.close();

        for (unsigned long c = 0; c < info_reader.num_channels(); c++) {
            os << calculator.get(c);
            if (c + 1 < info_reader.num_channels()) {
                os << "\t";
            }
        }
        os << endl;

    } catch (IOException& e) {
        cerr << e.get_message() << endl;
    }

}

void WvToolsFacade::write_quality(std::ostream &os, const std::string &prefix, const unsigned int &channel, const std::string &svm, const bool &headers, const std::string &annotation_file) {
    try {
        InfoReader info_reader(prefix);
        WvReader wv_reader(prefix);
        QrsOnsetReader annotation_reader(annotation_file);
        SvmParams svm_params(svm);

        FeatureCalculator feature_calculator(annotation_reader.get_onsets(), wv_reader.num_entries() / info_reader.num_channels());

        QualityChecker quality_checker(625, svm_params);

        unsigned long current_index = 0;
        vector<double> current_observations;
        while (wv_reader.has_next()) {
            if (current_index++ % info_reader.num_channels() == channel) {
                current_observations.push_back(info_reader.gains[channel] * wv_reader.next());
            } else {
                wv_reader.next();
            }
            if (current_observations.size() == 625) {
                quality_checker.read(feature_calculator.calculate_features(current_observations, current_index / info_reader.num_channels() - 624));
                current_observations.clear();
            }
        }

        if (headers) {
            quality_checker.print_stats(os);
        }

        quality_checker.print_qualities(os);

    } catch (IOException &e) {
        cerr << e.get_message() << endl;
    }
}


void WvToolsFacade::write_features(std::ostream &os, const std::string &prefix, const unsigned int &channel, const bool &headers, const std::string &annotation_file) {
    try {
        InfoReader info_reader(prefix);
        WvReader wv_reader(prefix);
        QrsOnsetReader annotation_reader(annotation_file);
        FeatureCalculator feature_calculator(annotation_reader.get_onsets(), wv_reader.num_entries() / info_reader.num_channels());

        if (headers) {
            os << "WindowMean\tWindowVar\tWindowStdev\tWindowRange\tNumConst\tQrsMean\tQrsStdev\tQrsRange" << endl;
        }

        unsigned long current_index = 0;
        vector<double> current_observations;
        while (wv_reader.has_next()) {
            if (current_index++ % info_reader.num_channels() == channel) {
                current_observations.push_back(info_reader.gains[channel] * wv_reader.next());
            } else {
                wv_reader.next();
            }
            if (current_observations.size() == 625) {
                vector<double> features = feature_calculator.calculate_features(current_observations, current_index / info_reader.num_channels() - 624);
                for (unsigned long c = 0; c < features.size() - 1; c++) {
                    os << features[c] << "\t";
                }
                os << features[features.size() - 1] << endl;
                current_observations.clear();
            }
        }

    } catch (IOException &e) {
        cerr << e.get_message() << endl;
    }
}


void WvToolsFacade::write_num_channels(std::ostream &os, const std::string &prefix) {
    try {
        InfoReader info_reader(prefix);
        os << info_reader.num_channels() << endl;
    } catch (IOException& e) {
        cerr << e.get_message() << endl;
    }
}


void WvToolsFacade::tsdb_upload(const std::string &prefix, const unsigned int &channel, const std::string &svm,
                                const std::string &qrs_file, const std::string &tsdb_root) {
    try {
        InfoReader info_reader(prefix);
        WvReader wv_reader(prefix);

    } catch (IOException & e) {
        cerr << e.get_message() << endl;
    }

}



