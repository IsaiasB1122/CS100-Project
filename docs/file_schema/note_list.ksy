meta:
  id: cataboard_note_list
  file-extension: cnl
  endian: le
types:
  string:
    seq:
      - id: len
        type: u4
      - id: data
        type: strz
        encoding: UTF-8
        size: len
  note_entry:
    seq:
      - id: id
        type: u4
      - id: name
        type: string
      - id: text
        type: string
      - id: author_id
        type: u4
      - id: time_created
        type: u8
      - id: time_modified
        type: u8
seq:
  - id: magic
    contents: "CTNL"
  - id: next_note_id
    type: u4
  - id: note_num
    type: u4
  - id: note
    type: u4
    repeat: note_entry