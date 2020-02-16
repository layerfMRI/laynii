
#include "./common.h"
#include "./renzo_stat.h"

int show_help(void) {
    printf(
    "LN_CORREL2FILES: Estimate the voxel wise correlation of two timeseries.\n"
    "\n"
    "    This program is motivated by Eli Merriam comparing in hunting down \n"
    "    voxels that out of phase for VASO and BOLD. \n"
    "\n"
    "Usage:\n"
    "    LN_CORREL2FILES -file1 file1.nii -file2 file2.nii \n"
    "\n"
    "Options:\n"
    "    -help  : Show this help.\n"
    "    -file1 : First time series.\n"
    "    -file2 : Second time series with should have the same dimensions \n"
    "             as first time series.\n"
    "\n");
    return 0;
}

int main(int argc, char * argv[]) {
    // nifti_image * nim_input=NULL;
    char *fin_1 = NULL, *fin_2 = NULL;
    int ac, disp_float_eg = 0;
    if (argc < 2) {  // Typing '-help' is sooo much work
       return show_help();
    }

    // Process user options
    for (ac = 1; ac < argc; ac++) {
        if (!strncmp(argv[ac], "-h", 2)) {
            return show_help();
        } else if (!strcmp(argv[ac], "-file1")) {
            if (++ac >= argc) {
                fprintf(stderr, "** missing argument for -file1\n");
                return 1;
            }
            fin_1 = argv[ac];  // Assign pointer, no string copy
        } else if (!strcmp(argv[ac], "-file2")) {
            if (++ac >= argc) {
                fprintf(stderr, "** missing argument for -file2\n");
                return 1;
            }
            fin_2 = argv[ac];  // Assign pointer, no string copy
        } else {
            fprintf(stderr, "** invalid option, '%s'\n", argv[ac]);
            return 1;
        }
    }

    if (!fin_1) {
        fprintf(stderr, "** missing option '-file1'\n");
        return 1;
    }
    // Read input dataset, including data
    nifti_image * nim_file_1i = nifti_image_read(fin_1, 1);
    if (!nim_file_1i) {
        fprintf(stderr, "** failed to read NIfTI image from '%s'\n", fin_1);
        return 2;
    }
    if (!fin_2) {
        fprintf(stderr, "** missing option '-file2'\n");
        return 1;
    }
    // Read input dataset, including data
    nifti_image *nim_file_2i = nifti_image_read(fin_2, 1);
    if (!nim_file_2i) {
        fprintf(stderr, "** failed to read NIfTI image from '%s'\n", fin_2);
        return 2;
    }

    // Get dimensions of input
    int sizeSlice = nim_file_1i->nz;
    int sizePhase = nim_file_1i->nx;
    int sizeRead = nim_file_1i->ny;
    int nrep = nim_file_1i->nt;
    int nx = nim_file_1i->nx;
    int nxy = nim_file_1i->nx * nim_file_1i->ny;
    int nxyz = nim_file_1i->nx * nim_file_1i->ny * nim_file_1i->nz;

    cout << sizeSlice << " Slices " << sizePhase << " | PhaseSteps " << sizeRead << " | Read steps " << nrep << " | Timesteps " << endl;

    nifti_image * nim_file_1 = nifti_copy_nim_info(nim_file_1i);
    nim_file_1->datatype = NIFTI_TYPE_FLOAT32;
    nim_file_1->nbyper = sizeof(float);
    nim_file_1->data = calloc(nim_file_1->nvox, nim_file_1->nbyper);
    float *nim_file_1_data = (float *) nim_file_1->data;

    nifti_image * nim_file_2 = nifti_copy_nim_info(nim_file_1i);
    nim_file_2->datatype = NIFTI_TYPE_FLOAT32;
    nim_file_2->nbyper = sizeof(float);
    nim_file_2->data = calloc(nim_file_2->nvox, nim_file_2->nbyper);
    float *nim_file_2_data = (float *) nim_file_2->data;

    // if (!fout) {
    //     fprintf(stderr, "-- no output requested \n");
    //     return 0;
    // }
    // // Assign nifti_image fname/iname pair, based on output filename
    // // (request to 'check' image and 'set_byte_order' here)
    // if (nifti_set_filenames(nim_input, fout, 1, 1)) {
    //     return 1;
    // }

    if (nim_file_1i->datatype == NIFTI_TYPE_FLOAT32) {
        float *nim_file_1i_data = (float *) nim_file_1i->data;
        for (int it = 0; it < nrep; ++it) {
            for (int islice = 0; islice < sizeSlice; ++islice) {
                for (int iy = 0; iy < sizePhase; ++iy) {
                    for (int ix = 0; ix < sizeRead; ++ix) {
                        *(nim_file_1_data + nxyz * it + nxy * islice + nx * ix + iy) = (float) (*(nim_file_1i_data + nxyz * it + nxy * islice + nx * ix + iy));
                    }
                }
            }
        }
    }
    if (nim_file_1i->datatype == NIFTI_TYPE_INT16) {
        short *nim_file_1i_data = (short *) nim_file_1i->data;
        for (int it = 0; it < nrep; ++it) {
            for (int islice = 0; islice < sizeSlice; ++islice) {
                for (int iy = 0; iy < sizePhase; ++iy) {
                    for (int ix = 0; ix < sizeRead; ++ix) {
                        *(nim_file_1_data + nxyz * it + nxy * islice + nx * ix + iy) = (float) (*(nim_file_1i_data + nxyz * it + nxy * islice + nx * ix + iy));
                    }
                }
            }
        }
    }
    if (nim_file_1i->datatype == NIFTI_TYPE_FLOAT32) {
        float *nim_file_1i_data = (float *) nim_file_1i->data;
        for (int it = 0; it < nrep; ++it) {
            for (int islice = 0; islice < sizeSlice; ++islice) {
                for (int iy = 0; iy < sizePhase; ++iy) {
                    for (int ix = 0; ix < sizeRead; ++ix) {
                        *(nim_file_1_data + nxyz * it + nxy * islice + nx * ix + iy) = (float) (*(nim_file_1i_data + nxyz * it + nxy * islice + nx * ix + iy));
                    }
                }
            }
        }
    }
    if (nim_file_2i->datatype == NIFTI_TYPE_INT16) {
        short *nim_file_2i_data = (short *) nim_file_2i->data;
        for (int it = 0; it < nrep; ++it) {
            for (int islice = 0; islice < sizeSlice; ++islice) {
                for (int iy = 0; iy < sizePhase; ++iy) {
                    for (int ix = 0; ix < sizeRead; ++ix) {
                        *(nim_file_2_data + nxyz * it + nxy * islice + nx * ix + iy) = (float) (*(nim_file_2i_data + nxyz * it + nxy * islice + nx * ix + iy));
                    }
                }
            }
        }
    }
    if (nim_file_2i->datatype == NIFTI_TYPE_FLOAT32) {
        float *nim_file_2i_data = (float *) nim_file_2i->data;
        for (int it = 0; it < nrep; ++it) {
            for (int islice = 0; islice < sizeSlice; ++islice) {
                for (int iy = 0; iy < sizePhase; ++iy) {
                    for (int ix = 0; ix < sizeRead; ++ix) {
                        *(nim_file_2_data + nxyz * it + nxy * islice + nx * ix + iy) = (float) (*(nim_file_2i_data + nxyz * it + nxy * islice + nx * ix + iy));
                    }
                }
            }
        }
    }

    nifti_image * correl_file = nifti_copy_nim_info(nim_file_1);
    correl_file->nt = 1;
    correl_file->nvox = nim_file_1->nvox / nrep;
    correl_file->datatype = NIFTI_TYPE_FLOAT32;
    correl_file->nbyper = sizeof(float);
    correl_file->data = calloc(correl_file->nvox, correl_file->nbyper);
    float *correl_file_data = (float *) correl_file->data;

    double vec_file1[nrep];
    double vec_file2[nrep];

    for (int islice = 0; islice < sizeSlice; ++islice) {
        for (int iy = 0; iy < sizePhase; ++iy) {
            for (int ix = 0; ix < sizeRead; ++ix) {
                for (int it = 0;  it < nrep; ++it) {
                    vec_file1[it] = *(nim_file_1_data + nxyz * it + nxy * islice + nx * ix + iy);
                    vec_file2[it] = *(nim_file_2_data + nxyz * it + nxy * islice + nx * ix + iy);
                }
                // cout << ren_correl(vec_file1, vec_file2, nrep) << "     " << gsl_stats_correlation(vec_file1, 1, vec_file2, 1, nrep) << endl;
                *(correl_file_data + nxy * islice + nx * ix + iy) = ren_correl(vec_file1, vec_file2, nrep);
            }
        }
    }
    cout << "  Running also until here  5... " << endl;

    string prefix = "correlated_";
    string filename_1 = (string) (fin_1);
    string outfilename = prefix+filename_1;

    cout << "  Writing as = " << outfilename.c_str() << endl;

    const char *fout_1 = outfilename.c_str();
    if (nifti_set_filenames(correl_file, fout_1, 1, 1)) {
        return 1;
    }
    nifti_image_write(correl_file);

    // const char *fout_5 = "debug_ing.nii";
    // if (nifti_set_filenames(growfromWM0, fout_5, 1, 1)) {
    //     return 1;
    // }
    // nifti_image_write(growfromWM0);

    // const char *fout_6 = "kootrGM.nii";
    // if (nifti_set_filenames(GMkoord2, fout_6, 1, 1)) {
    //     return 1;
    // }
    // nifti_image_write(GMkoord2);

    // koord.autowrite("koordinaten.nii", wopts, &prot);
    cout << "  Finished." << endl;
    return 0;
}
