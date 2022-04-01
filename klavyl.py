from klavgen import *
from dataclasses import dataclass

config = Config(
    case_config=CaseConfig(side_fillet=4),
    key_config=KeyConfig(case_tile_margin=7.5),
    controller_config=ControllerConfig(case_tile_margin=5),
    trrs_jack_config=TrrsJackConfig(case_tile_margin=5),
)

size_1u = 18
size_15u = 23
key_gap = 1.05


@dataclass
class Col:
    horz_size: float
    vert_offset: float
    num_rows: int
    horz_offset: float = 0


cols = [
    Col(size_15u, -1, 4),
    Col(size_1u, -3, 4),
    Col(size_1u, 4.5, 4, horz_offset=3),
    Col(size_1u, 8, 4, horz_offset=1),
    Col(size_1u, 3.5, 4),
    Col(size_1u, 2, 4),
    Col(size_1u, -3, 4),
]

keys = []
x = 0
y = 0
for col in cols:
    y = 0 + col.vert_offset
    x += col.horz_size / 2 + col.horz_offset
    for row_index in range(col.num_rows):
        y -= size_1u / 2
        keys.append(Key(x=x, y=y, keycap_width=col.horz_size, keycap_depth=size_1u))
        y -= size_1u / 2 + key_gap
    x += col.horz_size / 2 + key_gap

# Thumb cluster
cluster_x = 108
cluster_y = -86

keys.append(Key(x=cluster_x, y=cluster_y, rotate=-25, keycap_width=23, keycap_depth=18))

second_offset_x = 20
second_offset_y = -12.5
cluster_second_x = cluster_x + second_offset_x
cluster_second_y = cluster_y + second_offset_y
keys.extend(
    [
        Key(
            x=cluster_second_x,
            y=cluster_second_y,
            rotate=-40,
            keycap_width=18,
            keycap_depth=23,
        ),
        Key(
            x=cluster_second_x + size_1u + key_gap,
            y=cluster_second_y,
            rotate=-40,
            rotate_around=(cluster_second_x, cluster_second_y),
            keycap_width=18,
            keycap_depth=23,
        ),
    ]
)

screw_holes = [  # Clockwise
    ScrewHole(x=2.5, y=8.5, z=0),
    ScrewHole(x=137, y=8.5, z=0),
    ScrewHole(x=149, y=-38.4, z=0),
    ScrewHole(x=141.5, y=-86, z=0),
    ScrewHole(x=143.5, y=-129.5, z=0),
    ScrewHole(x=2.5, y=-87.7, z=0),
]

patches = [
    Patch(
        points=[
            (-3, 14),
            (147, 14),
            (147, -100),
            (90, -93.2),
            (-3, -93.2),
        ],
        height=config.case_config.case_base_height,
    ),
    Patch(
        points=[
            (140, 14),
            (171.9, 14),
            (171.9, -43.9),
            (140, -43.9),
        ],
        height=config.case_config.case_base_height,
    ),
]

palm_rests = [
    PalmRest(
        points=[
            (-3, -80),
            (120, -80),
            (146.7888827948367, -128.30281581958877),
            (93.34059904202246, -192),
            (-3, -192),
        ],
        height=config.case_config.case_base_height + 8,
        connector_locations_x=[20, 125],
    ),
]

texts = [
    # Text(x=16, y=7, z=0, text="v10", font_size=10, extrude=0.4),
    # Text(x=11, y=-102, z=8, text="v10", font_size=10, extrude=0.4)
]

controller = Controller(x=154, y=14)

trrs_jack = TrrsJack(x=171.9, y=-32, rotate=-90)


keyboard_result = render_and_save_keyboard(
    keys=keys,
    screw_holes=screw_holes,
    controller=controller,
    trrs_jack=trrs_jack,
    patches=patches,
    palm_rests=palm_rests,
    texts=texts,
    debug=False,
    render_standard_components=True,
    config=config,
)

print("Done")