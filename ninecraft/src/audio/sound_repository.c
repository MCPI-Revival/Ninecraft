#define OGG_IMPL
#define VORBIS_IMPL
#include <minivorbis.h>
#include <ninecraft/audio/sound_repository.h>
#include <string.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>

static ninecraft_sound_t ninecraft_sound_repository[] = {
    {
        .name = "random.pop2",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "pop2.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.cloth",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "cloth1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "cloth2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "cloth3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "cloth4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.grass",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "grass1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "grass2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "grass3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "grass4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.gravel",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "gravel1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "gravel2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "gravel3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "gravel4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.sand",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "sand1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "sand2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "sand3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "sand4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.stone",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "stone1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "stone2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "stone3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "stone4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.wood",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "wood1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "wood2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "wood3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "wood4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.click",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "click.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.explode",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "explode.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.splash",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "splash.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.door_open",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "door_open.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.door_close",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "door_close.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.pop",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "pop.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "hurt.pop",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "hurt.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "hurt.glass",
        .resources_count = 3,
        .resources = {
            .a = {
                .name = "glass1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "glass2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "glass3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.sheep",
        .resources_count = 3,
        .resources = {
            .a = {
                .name = "sheep1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "sheep2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "sheep3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.pig",
        .resources_count = 3,
        .resources = {
            .a = {
                .name = "pig1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "pig2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "pig3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.pigdeath",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "pigdeath.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.chicken",
        .resources_count = 2,
        .resources = {
            .a = {
                .name = "chicken2.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "chicken3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.chickenhurt",
        .resources_count = 2,
        .resources = {
            .a = {
                .name = "chickenhurt1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "chickenhurt2.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.cow",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "cow1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "cow2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "cow3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "cow4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.cowhurt",
        .resources_count = 3,
        .resources = {
            .a = {
                .name = "cowhurt1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "cowhurt2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "cowhurt3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombie",
        .resources_count = 3,
        .resources = {
            .a = {
                .name = "zombie1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "zombie2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "zombie3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiepig.zpig",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "zpig1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "zpig2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "zpig3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "zpig4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiepig.zpigangry",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "zpigangry1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "zpigangry2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "zpigangry3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "zpigangry4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiepig.zpigdeath",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "zpigdeath.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiepig.zpighurt",
        .resources_count = 2,
        .resources = {
            .a = {
                .name = "zpighurt1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "zpighurt2.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiedeath",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "zombiedeath.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiehurt",
        .resources_count = 2,
        .resources = {
            .a = {
                .name = "zombiehurt1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "zombiehurt2.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.bow",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "bow.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.bowhit",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "bowhit1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "bowhit2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "bowhit3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "bowhit4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "damage.fallbig",
        .resources_count = 2,
        .resources = {
            .a = {
                .name = "fallbig1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "fallbig2.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "damage.fallsmall",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "fallsmall.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.skeleton",
        .resources_count = 3,
        .resources = {
            .a = {
                .name = "skeleton1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "skeleton2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "skeleton3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.skeletonhurt",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "skeletonhurt1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "skeletonhurt2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "skeletonhurt3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "skeletonhurt4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.spider",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "spider1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "spider2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "spider3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "spider4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.spiderdeath",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "spiderdeath.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.creeper",
        .resources_count = 4,
        .resources = {
            .a = {
                .name = "creeper1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "creeper2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "creeper3.ogg",
                .buffer = NULL
            },
            .d = {
                .name = "creeper4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.creeperdeath",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "creeperdeath.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.eat",
        .resources_count = 3,
        .resources = {
            .a = {
                .name = "eat1.ogg",
                .buffer = NULL
            },
            .b = {
                .name = "eat2.ogg",
                .buffer = NULL
            },
            .c = {
                .name = "eat3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.fuse",
        .resources_count = 1,
        .resources = {
            .a = {
                .name = "fuse.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = NULL,
        .resources_count = 0,
        .resources = {
            .a = {
                .name = NULL,
                .buffer = NULL
            },
            .b = {
                .name = NULL,
                .buffer = NULL
            },
            .c = {
                .name = NULL,
                .buffer = NULL
            },
            .d = {
                .name = NULL,
                .buffer = NULL
            }
        }
    }
};

ninecraft_sound_resource_t *ninecraft_get_sound_buffer(char *name) {
    for (int i = 0; ninecraft_sound_repository[i].name != NULL; ++i) {
        ninecraft_sound_t *sound = ninecraft_sound_repository + i;
        if (strcmp(sound->name, name) == 0) {
            srand(time(NULL));
            int resource_index = rand() % sound->resources_count;
            ninecraft_sound_resource_t *resource = ((ninecraft_sound_resource_t *)&sound->resources) + resource_index;
            if (resource->buffer == NULL) {
                char path[MAXPATHLEN];
                getcwd(path, MAXPATHLEN);
                strcat(path, "/res/raw/");
                strcat(path, resource->name);
                FILE *fp = fopen(path, "r");
                if (fp != NULL) {
                    OggVorbis_File vorbis;
                    if (ov_open_callbacks(fp, &vorbis, NULL, 0, OV_CALLBACKS_NOCLOSE) == 0) {
                        vorbis_info* info = ov_info(&vorbis, -1);
                        resource->bits_per_sample = 16;
                        resource->num_channels = info->channels;
                        resource->freq = info->rate;
                        resource->buffer_size = ov_pcm_total(&vorbis, -1) * info->channels * 2;
                        resource->buffer = (uint8_t *)malloc(resource->buffer_size);

                        long size = 0;
                        size_t offset = 0;
                        int sel = 0;
                        while ((size = ov_read(&vorbis, resource->buffer + offset, 4096, 0, 2, 1, &sel)) != 0) {
                            if (size < 0) {
                                puts("[SOUND_REPOSITORY] Broken audio sample.");
                            }
                            offset += size;
                        }
                    }
                    fclose(fp);
                    ov_clear(&vorbis);
                }
            }
            return resource;
        }
    }
    return NULL;
}