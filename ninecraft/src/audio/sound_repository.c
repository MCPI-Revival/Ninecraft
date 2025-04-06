#define OGG_IMPL
#define VORBIS_IMPL
#include <minivorbis.h>
#include <ninecraft/audio/sound_repository.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <direct.h>
#endif

static ninecraft_sound_t ninecraft_sound_repository[] = {
    {
        .name = "random.pop2",
        .resources_count = 1,
        .resources = {
            {
                .name = "pop2.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.cloth",
        .resources_count = 4,
        .resources = {
            {
                .name = "cloth1.ogg",
                .buffer = NULL
            },
            {
                .name = "cloth2.ogg",
                .buffer = NULL
            },
            {
                .name = "cloth3.ogg",
                .buffer = NULL
            },
            {
                .name = "cloth4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.grass",
        .resources_count = 4,
        .resources = {
            {
                .name = "grass1.ogg",
                .buffer = NULL
            },
            {
                .name = "grass2.ogg",
                .buffer = NULL
            },
            {
                .name = "grass3.ogg",
                .buffer = NULL
            },
            {
                .name = "grass4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.gravel",
        .resources_count = 3,
        .resources = {
            {
                .name = "gravel2.ogg",
                .buffer = NULL
            },
            {
                .name = "gravel3.ogg",
                .buffer = NULL
            },
            {
                .name = "gravel4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.sand",
        .resources_count = 4,
        .resources = {
            {
                .name = "sand1.ogg",
                .buffer = NULL
            },
            {
                .name = "sand2.ogg",
                .buffer = NULL
            },
            {
                .name = "sand3.ogg",
                .buffer = NULL
            },
            {
                .name = "sand4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.stone",
        .resources_count = 4,
        .resources = {
            {
                .name = "stone1.ogg",
                .buffer = NULL
            },
            {
                .name = "stone2.ogg",
                .buffer = NULL
            },
            {
                .name = "stone3.ogg",
                .buffer = NULL
            },
            {
                .name = "stone4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "step.wood",
        .resources_count = 4,
        .resources = {
            {
                .name = "wood1.ogg",
                .buffer = NULL
            },
            {
                .name = "wood2.ogg",
                .buffer = NULL
            },
            {
                .name = "wood3.ogg",
                .buffer = NULL
            },
            {
                .name = "wood4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.click",
        .resources_count = 1,
        .resources = {
            {
                .name = "click.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.explode",
        .resources_count = 1,
        .resources = {
            {
                .name = "explode.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.splash",
        .resources_count = 1,
        .resources = {
            {
                .name = "splash.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.door_open",
        .resources_count = 1,
        .resources = {
            {
                .name = "door_open.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.door_close",
        .resources_count = 1,
        .resources = {
            {
                .name = "door_close.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.pop",
        .resources_count = 1,
        .resources = {
            {
                .name = "pop.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "hurt.pop",
        .resources_count = 1,
        .resources = {
            {
                .name = "hurt.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "hurt.glass",
        .resources_count = 3,
        .resources = {
            {
                .name = "glass1.ogg",
                .buffer = NULL
            },
            {
                .name = "glass2.ogg",
                .buffer = NULL
            },
            {
                .name = "glass3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.sheep",
        .resources_count = 3,
        .resources = {
            {
                .name = "sheep1.ogg",
                .buffer = NULL
            },
            {
                .name = "sheep2.ogg",
                .buffer = NULL
            },
            {
                .name = "sheep3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.pig",
        .resources_count = 3,
        .resources = {
            {
                .name = "pig1.ogg",
                .buffer = NULL
            },
            {
                .name = "pig2.ogg",
                .buffer = NULL
            },
            {
                .name = "pig3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.pigdeath",
        .resources_count = 1,
        .resources = {
            {
                .name = "pigdeath.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.chicken",
        .resources_count = 2,
        .resources = {
            {
                .name = "chicken2.ogg",
                .buffer = NULL
            },
            {
                .name = "chicken3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.chickenhurt",
        .resources_count = 2,
        .resources = {
            {
                .name = "chickenhurt1.ogg",
                .buffer = NULL
            },
            {
                .name = "chickenhurt2.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.cow",
        .resources_count = 4,
        .resources = {
            {
                .name = "cow1.ogg",
                .buffer = NULL
            },
            {
                .name = "cow2.ogg",
                .buffer = NULL
            },
            {
                .name = "cow3.ogg",
                .buffer = NULL
            },
            {
                .name = "cow4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.cowhurt",
        .resources_count = 3,
        .resources = {
            {
                .name = "cowhurt1.ogg",
                .buffer = NULL
            },
            {
                .name = "cowhurt2.ogg",
                .buffer = NULL
            },
            {
                .name = "cowhurt3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombie",
        .resources_count = 3,
        .resources = {
            {
                .name = "zombie1.ogg",
                .buffer = NULL
            },
            {
                .name = "zombie2.ogg",
                .buffer = NULL
            },
            {
                .name = "zombie3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiepig.zpig",
        .resources_count = 4,
        .resources = {
            {
                .name = "zpig1.ogg",
                .buffer = NULL
            },
            {
                .name = "zpig2.ogg",
                .buffer = NULL
            },
            {
                .name = "zpig3.ogg",
                .buffer = NULL
            },
            {
                .name = "zpig4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiepig.zpigangry",
        .resources_count = 4,
        .resources = {
            {
                .name = "zpigangry1.ogg",
                .buffer = NULL
            },
            {
                .name = "zpigangry2.ogg",
                .buffer = NULL
            },
            {
                .name = "zpigangry3.ogg",
                .buffer = NULL
            },
            {
                .name = "zpigangry4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiepig.zpigdeath",
        .resources_count = 1,
        .resources = {
            {
                .name = "zpigdeath.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiepig.zpighurt",
        .resources_count = 2,
        .resources = {
            {
                .name = "zpighurt1.ogg",
                .buffer = NULL
            },
            {
                .name = "zpighurt2.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiedeath",
        .resources_count = 1,
        .resources = {
            {
                .name = "zombiedeath.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.zombiehurt",
        .resources_count = 2,
        .resources = {
            {
                .name = "zombiehurt1.ogg",
                .buffer = NULL
            },
            {
                .name = "zombiehurt2.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.bow",
        .resources_count = 1,
        .resources = {
            {
                .name = "bow.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.bowhit",
        .resources_count = 4,
        .resources = {
            {
                .name = "bowhit1.ogg",
                .buffer = NULL
            },
            {
                .name = "bowhit2.ogg",
                .buffer = NULL
            },
            {
                .name = "bowhit3.ogg",
                .buffer = NULL
            },
            {
                .name = "bowhit4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "damage.fallbig",
        .resources_count = 2,
        .resources = {
            {
                .name = "fallbig1.ogg",
                .buffer = NULL
            },
            {
                .name = "fallbig2.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "damage.fallsmall",
        .resources_count = 1,
        .resources = {
            {
                .name = "fallsmall.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.skeleton",
        .resources_count = 3,
        .resources = {
            {
                .name = "skeleton1.ogg",
                .buffer = NULL
            },
            {
                .name = "skeleton2.ogg",
                .buffer = NULL
            },
            {
                .name = "skeleton3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.skeletonhurt",
        .resources_count = 4,
        .resources = {
            {
                .name = "skeletonhurt1.ogg",
                .buffer = NULL
            },
            {
                .name = "skeletonhurt2.ogg",
                .buffer = NULL
            },
            {
                .name = "skeletonhurt3.ogg",
                .buffer = NULL
            },
            {
                .name = "skeletonhurt4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.spider",
        .resources_count = 4,
        .resources = {
            {
                .name = "spider1.ogg",
                .buffer = NULL
            },
            {
                .name = "spider2.ogg",
                .buffer = NULL
            },
            {
                .name = "spider3.ogg",
                .buffer = NULL
            },
            {
                .name = "spider4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.spiderdeath",
        .resources_count = 1,
        .resources = {
            {
                .name = "spiderdeath.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.creeper",
        .resources_count = 4,
        .resources = {
            {
                .name = "creeper1.ogg",
                .buffer = NULL
            },
            {
                .name = "creeper2.ogg",
                .buffer = NULL
            },
            {
                .name = "creeper3.ogg",
                .buffer = NULL
            },
            {
                .name = "creeper4.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "mob.creeperdeath",
        .resources_count = 1,
        .resources = {
            {
                .name = "creeperdeath.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.eat",
        .resources_count = 3,
        .resources = {
            {
                .name = "eat1.ogg",
                .buffer = NULL
            },
            {
                .name = "eat2.ogg",
                .buffer = NULL
            },
            {
                .name = "eat3.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = "random.fuse",
        .resources_count = 1,
        .resources = {
            {
                .name = "fuse.ogg",
                .buffer = NULL
            }
        }
    },
    {
        .name = NULL,
        .resources_count = 0,
        .resources = {
            {
                .name = NULL,
                .buffer = NULL
            },
            {
                .name = NULL,
                .buffer = NULL
            },
            {
                .name = NULL,
                .buffer = NULL
            },
            {
                .name = NULL,
                .buffer = NULL
            }
        }
    }
};

ninecraft_sound_resource_t *ninecraft_get_sound_buffer(char *name) {
    for (int i = 0; ninecraft_sound_repository[i].name != NULL; ++i) {
        ninecraft_sound_t *sound = &ninecraft_sound_repository[i];
        if (strcmp(sound->name, name) == 0) {
            srand(time(NULL));
            int resource_index = rand() % sound->resources_count;
            ninecraft_sound_resource_t *resource = &sound->resources[resource_index];
            if (resource->buffer == NULL) {
                char *path = (char *)malloc(1024);
                path[0] = '\0';
                getcwd(path, 1024);
                strcat(path, "/res/raw/");
                strcat(path, resource->name);
                FILE *fp = fopen(path, "rb");
                if (fp != NULL) {
                    OggVorbis_File vorbis;
                    if (ov_open_callbacks(fp, &vorbis, NULL, 0, OV_CALLBACKS_DEFAULT) == 0) {
                        vorbis_info* info = ov_info(&vorbis, -1);
                        resource->bits_per_sample = 16;
                        resource->num_channels = info->channels;
                        resource->freq = info->rate;
                        resource->buffer_size = ov_pcm_total(&vorbis, -1) * info->channels * 2;
                        resource->buffer = (uint8_t *)malloc(resource->buffer_size);

                        long size = 0;
                        size_t offset = 0;
                        int sel = 0;
                        while ((size = ov_read(&vorbis, resource->buffer + offset, resource->buffer_size, 0, 2, 1, &sel)) != 0) {
                            if (size < 0) {
                                puts("[SOUND_REPOSITORY] Broken audio sample.");
                            }
                            offset += (size_t)size;
                        }
                    }
                    ov_clear(&vorbis);
                }
                free(path);
            }
            return resource;
        }
    }
    return NULL;
}