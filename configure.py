#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path

from tools.project import (
    Object,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 3  # RSBE01_02
VERSIONS = [
    "RSBJ01_00",  # Japan Rev 0 (January 31, 2008)
    "RSBJ01_01",  # Japan Rev 1 (?)
    "RSBE01_01",  # USA Rev 1 (March 9, 2008)
    "RSBE01_02",  # USA Rev 2 (?)
    "RSBP01_00",  # PAL Rev 0 (June 27, 2008)
    "RSBP01_01",  # PAL Rev 1 (?)
    "RSBK01_00",  # Korea Rev 0 (April 29, 2010)
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20250812"
config.dtk_tag = "v1.7.5"
config.objdiff_tag = "v3.4.4"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.0"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
    f"--defsym VERSION_{config.version}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-enc SJIS",
    "-i include",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

cflags_common = [
    *cflags_base,
    "-DMATCHING",
    "-Iinclude",
    "-Iinclude/lib/PowerPC_EABI_Support/Runtime/Inc",
    "-Iinclude/lib/BrawlHeaders/Brawl/Include",
    "-Iinclude/lib/BrawlHeaders/nw4r/include",
    "-Iinclude/lib/BrawlHeaders/OpenRVL/include",
    "-Iinclude/lib/BrawlHeaders/OpenRVL/include/MetroTRK",
    "-Iinclude/lib/BrawlHeaders/OpenRVL/include/revolution",
    "-Iinclude/lib/BrawlHeaders/OpenRVL/include/RVLFaceLib",
    "-Iinclude/lib/BrawlHeaders/OpenRVL/include/stl",
    "-Iinclude/lib/BrawlHeaders/utils/include",
    "-RTTI on",
    "-ipa file",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

# REL flags
config.rel_strip_partial = True
cflags_rel = [
    *cflags_common,
    "-sdata 0",
    "-sdata2 0",
]

cflags_sora_enemy = ["-O2,s" if flag == "-O4,p" else flag for flag in cflags_rel]
cflags_st_starfox = [*cflags_rel, "-inline on,noauto"]

config.linker_version = "GC/3.0a5.2"

Matching = True  # Object matches and should be linked
NonMatching = False  # Object does not match and should not be linked
Equivalent = (
    config.non_matching
)  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "host": False,
        "objects": [
            Object(NonMatching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
        ],
    },
    # The DOL
    {
        "lib": "sora",
        "mw_version": config.linker_version,
        "cflags": cflags_common,
        "host": False,
        "objects": [
            Object(Matching, "sora/sr/sr_getappname.cpp"),
            Object(Matching, "sora/sr/sr_common.cpp"),
            Object(Matching, "sora/sr/sr_revision.cpp"),
            Object(Matching, "sora/main.cpp"),
            Object(Matching, "sora/gf/gf_3d_scene_event.cpp"),
            Object(Matching, "sora/gf/gf_3d_scene_light_resource.cpp"),
            Object(Matching, "sora/gf/gf_archive_load_thread.cpp"),
            Object(Matching, "sora/gf/gf_archive_file.cpp"),
            Object(Matching, "sora/gf/gf_camera_controller.cpp"),
            Object(Matching, "sora/gf/gf_callback.cpp"),
            Object(Matching, "sora/gf/gf_decomp.cpp"),
            Object(Matching, "sora/gf/gf_error_check.cpp"),
            Object(Matching, "sora/gf/gf_file_io_handle.cpp"),
            Object(Matching, "sora/gf/gf_file_io_request.cpp"),
            Object(Matching, "sora/gf/gf_gameframe_counter.cpp"),
            Object(Matching, "sora/gf/gf_keep_fb.cpp"),
            Object(Matching, "sora/gf/gf_memory_util.cpp"),
            Object(Matching, "sora/gf/gf_pad_thread.cpp", extra_cflags=["-RTTI off"]),
            Object(Matching, "sora/gf/gf_task.cpp"),
            Object(NonMatching, "sora/gf/gf_task_scheduler.cpp"),
            Object(Matching, "sora/gf/gf_thread.cpp"),
            Object(Matching, "sora/gf/gf_system_callback.cpp"),
            Object(Matching, "sora/gf/gf_capture_util.cpp"),
            Object(Matching, "sora/gf/gf_monitor.cpp"),
            Object(Matching, "sora/gf/gf_resource_loader.cpp"),
            Object(NonMatching, "sora/mt/mt_vector_old.cpp"),
            Object(Matching, "sora/mt/mt_prng.cpp", extra_cflags=["-RTTI off"]),
            Object(Matching, "sora/mt/mt_prng_log.cpp"),
            Object(Matching, "sora/st/module.cpp"),
            Object(Matching, "sora/ut/ut_list.cpp"),
            Object(Matching, "sora/ip/ip_human.cpp"),
            Object(NonMatching, "sora/ip/ip_network_producer.cpp"),
            Object(Matching, "sora/ef/ef_screen_handle.cpp"),
            Object(Matching, "sora/snd/snd_init_thread.cpp"),
            Object(Matching, "sora/mv/mv_THPAudioDecode.cpp"),
            Object(Matching, "sora/cm/cm_controller_default.cpp", extra_cflags=["-RTTI off"]),
            Object(NonMatching, "sora/cm/cm_controller_menu_fixed.cpp"),
            Object(Matching, "sora/cm/cm_controller_melee_fixed.cpp"),
            Object(Matching, "sora/cm/cm_stage_param.cpp"),
            Object(NonMatching, "sora/ty/ty_fig_listmng.cpp"),
            Object(Matching, "sora/if/if_wifipr_task.cpp"),
            Object(Matching, "sora/if/if_adv_task.cpp"),
            Object(Matching, "sora/if/if_stgedit.cpp"),
            Object(Matching, "sora/gr/collision/gr_collision_data.cpp"),
            Object(Matching, "sora/gr/collision/gr_collision_handle.cpp"),
            Object(Matching, "sora/gr/gr_path.cpp"),
            Object(NonMatching, "sora/ac/ac_cmd_interpreter.cpp"),
            Object(Matching, "sora/ac/ac_anim_cmd_impl.cpp"),
            Object(Matching, "sora/ac/ac_null.cpp"),
            Object(Matching, "sora/ft/ft_system.cpp"),
            Object(Matching, "sora/nt/d_net_connect.cpp"),
            Object(Matching, "sora/nt/nt_etc_dwc.cpp", extra_cflags=["-RTTI off"]),
            Object(Matching, "sora/ad/ad_static_data.cpp"),
            Object(Matching, "sora/st/st_data_container.cpp"),
        ],
    },
    # Common REL units
    {
        "lib": "REL",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "mo_adv_menu/mo_adv_menu.cpp"),
            Object(Matching, "mo_fighter/mo_fighter.cpp"),
            Object(Matching, "mo_menu/mo_menu.cpp"),
            Object(Matching, "mo_stage/mo_stage.cpp"),
            Object(Matching, "global_destructor_chain.c"),
            Object(Matching, "home_button_icon.cpp"),
        ],
    },
    # The RELs
    {
        "lib": "ft_captain",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_dedede",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_diddy",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_donkey",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_falco",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_fox",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_gamewatch",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_ganon",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_iceclimber",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_ike",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_kirby",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_koopa",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_link",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_lucario",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_lucas",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_luigi",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_mario",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_marth",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_metaknight",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_ness",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_peach",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_pikachu",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_pikmin",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_pit",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_poke",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_purin",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_robot",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_samus",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_snake",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_sonic",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_toonlink",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_wario",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_wolf",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_yoshi",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_zako",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "ft_zelda",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_difficulty",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_ending",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_game_over",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_name",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_result",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_save_load",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_save_point",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_seal",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_sel_char",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_sel_map",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_telop",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_menu_visual",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_adv_stage",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "mo_adv_stage/mo_adv_stage.cpp"),
        ],
    },
    {
        "lib": "sora_enemy",
        "mw_version": config.linker_version,
        "cflags": cflags_sora_enemy,
        "host": False,
        "objects": [
            Object(Matching, "mo_enemy/sora_enemy/em_info.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/em_create.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/resource/em_resource_module_impl.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/stop/em_stop_module_impl.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/em_extend_param_accesser.cpp"),
            Object(NonMatching, "mo_enemy/sora_enemy/em_external_value_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/em_target_search_unit.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/wnem/wn_em_resource_module_impl.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/wnem/wn_em_heap_module_impl.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/boobas/em_boobas_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/siralamos/em_siralamos_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/roada/em_roada_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/killer/em_killer_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/popperam/em_popperam_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/pacci/em_pacci_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/jyakeel/em_jyakeel_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/aroaros/em_aroaros_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/cymal/em_cymal_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/deathpod/em_deathpod_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/dekakuribo/em_dekakuribo_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/bucyulus/em_bucyulus_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/botron/em_botron_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/gyraan/em_gyraan_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/mite/em_mite_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/prim/em_prim_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/cataguard/em_cataguard_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/wnem/wn_em_report.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/kuribo/em_kuribo_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/flows/em_flows_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/tautau/em_tautau_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/shelly/em_shelly_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/teckin/em_teckin_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/spar/em_spar_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/hammerbros/em_hammerbros_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/kokkon/em_kokkon_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/bombhead/em_bombhead_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/ngagog/em_ngagog_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/faulong/em_faulong_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/bitan/em_bitan_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/patapata/em_patapata_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/jdus/em_jdus_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/ghamgha/em_ghamgha_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/robobeam/em_robobeam_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/robodistance/em_robodistance_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/robohoming/em_robohoming_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/robopunch/em_robopunch_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/arman/em_arman_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/arman/wnem_proc_arman.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/galfire/em_galfire_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/bosspackun/em_bosspackun_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/ghamghabase/em_ghamghabase_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/galleom/em_galleom_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/ridley/em_ridley_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/rayquaza/em_rayquaza_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/rayquaza/wnem_proc_rayquaza.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/duon/em_duon_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/porky/em_porky_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/metaridley/em_metaridley_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/falconflyer/em_falconflyer_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/taboo/em_taboo_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/taboo/wnem_proc_taboo.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/masterhand/em_masterhand_param_accesser.cpp"),
            Object(Matching, "mo_enemy/sora_enemy/crazyhand/em_crazyhand_param_accesser.cpp"),
            Object(Matching, "mo_enemy/mo_enemy.cpp"),
        ],
    },
    {
        "lib": "sora_melee",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "mo_melee/sora_melee/so/model/so_model_module_impl_variable.cpp"),
            Object(Matching, "mo_melee/sora_melee/so/anim/so_anim_chr.cpp"),
            Object(Matching, "mo_melee/sora_melee/so/so_controller_module_link_ref.cpp"),
            Object(Matching, "mo_melee/sora_melee/so/so_heap_module_impl.cpp"),
            Object(Matching, "mo_melee/sora_melee/so/so_resource_module_impl.cpp"),
            Object(Matching, "mo_melee/sora_melee/so/so_general_work.cpp"),
            Object(Matching, "mo_melee/sora_melee/so/so_general_work_abstract.cpp"),
            Object(Matching, "mo_melee/sora_melee/so/so_general_work_simple.cpp"),
            Object(Matching, "mo_melee/sora_melee/so/anim/so_anim_cmd_interpreter_effect.cpp"),
            Object(Matching, "mo_melee/sora_melee/so/so_photo_call_back.cpp"),
            Object(Matching, "mo_melee/sora_melee/so/so_common_data_accesser.cpp"),
            Object(Matching, "mo_melee/mo_melee.cpp"),
        ],
    },
    {
        "lib": "sora_menu_boot",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_challenger",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_collect_viewer",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_edit",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_event",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_fig_get_demo",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_friend_list",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_game_over",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_intro",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_main",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_name",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_qm",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_replay",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_rule",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_sel_char",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_sel_char_access",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_sel_stage",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_simple_ending",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_snap_shot",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_time_result",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_title",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_title_sunset",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_tour",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_menu_watch",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_minigame",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "sora_scene",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "mo_scene/sora_scene/sc_demo.cpp"),
            Object(Matching, "mo_scene/sora_scene/sc_tutorial.cpp"),
            Object(Matching, "mo_scene/sora_scene/sc_staffroll.cpp"),
            Object(Matching, "mo_scene/sora_scene/sc_seal_list.cpp"),
            Object(Matching, "mo_scene/sora_scene/sc_seal_disp.cpp"),
            Object(Matching, "mo_scene/sora_scene/sc_net_time_result.cpp"),
            Object(Matching, "mo_scene/sora_scene/sc_adv_selchar.cpp"),
            Object(Matching, "mo_scene/sora_scene/sc_adv_saveload.cpp"),
            Object(Matching, "mo_scene/sora_scene/sc_adv_diff.cpp"),
            Object(Matching, "mo_scene/sora_scene/sc_adv_result.cpp"),
            Object(NonMatching, "mo_scene/sora_scene/sc_adv_gameover.cpp"),
            Object(Matching, "mo_scene/mo_scene.cpp"),
        ],
    },
    {
        "lib": "st_battle",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_battles",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_config",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "mo_stage/st_config/st_config.cpp"),
            Object(Matching, "mo_stage/st_config/gr_config.cpp"),
			],
    },
    {
        "lib": "st_crayon",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "mo_stage/st_crayon/st_crayon.cpp"),
            Object(Matching, "mo_stage/st_crayon/gr_crayon_yakumono.cpp"),
        ],
    },
    {
        "lib": "st_croll",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_dolpic",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_donkey",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_dxbigblue",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "mo_stage/st_dxbigblue/gr_dxbigblue.cpp"),
        ],
    },
    {
        "lib": "st_dxcorneria",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_dxgarden",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_dxgreens",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_dxonett",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_dxpstadium",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_dxrcruise",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_dxshrine",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
			Object(Matching, "mo_stage/st_dxshrine/st_dxshrine.cpp"),
			Object(Matching, "mo_stage/st_dxshrine/gr_dxshrine.cpp"),
			],
    },
    {
        "lib": "st_dxyorster",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_dxzebes",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_earth",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_emblem",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_famicom",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_final",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "mo_stage/st_final/st_final.cpp"),
            Object(Matching, "mo_stage/st_final/gr_final.cpp"),
			],
    },
    {
        "lib": "st_fzero",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_greenhill",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_gw",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_halberd",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_heal",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_homerun",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_ice",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_jungle",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_kart",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_madein",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_mansion",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_mariopast",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_metalgear",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_newpork",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_norfair",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_oldin",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_orpheon",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_otrain",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "mo_stage/st_otrain/st_onlinetrainning.cpp"),
        ],
    },
    {
        "lib": "st_palutena",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_pictchat",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_pirates",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_plankton",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_stadium",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_stageedit",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_starfox",
        "mw_version": config.linker_version,
        "cflags": cflags_st_starfox,
        "host": False,
        "objects": [
            Object(Matching, "mo_stage/st_starfox/st_starfox.cpp"),
        ],
    },
    {
        "lib": "st_tbreak",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_tengan",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
    {
        "lib": "st_village",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [],
    },
]

# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    # ProgressCategory("game", "Game Code"),
    # ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
