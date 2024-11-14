meta:
  id: cataboard_category_list
  file-extension: ccl
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
  category_entry:
    seq:
      - id: id
        type: u4
      - id: name
        type: string
seq:
  - id: magic
    contents: "CTCL"
  - id: next_category_id
    type: u4
  - id: category_num
    type: u4
  - id: category
    type: u4
    repeat: category_entry