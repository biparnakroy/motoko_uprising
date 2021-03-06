#include <line_mapping.h>

LineMapping::LineMapping()
{
    this->item_ptr  = 0;
    this->address   = 0;
}

LineMapping::~LineMapping()
{

}

void LineMapping::init()
{
    sLineMapItem init_item;

    init_item.position  = 0;
    init_item.value     = 0;

    this->buffer.fill(init_item);
    this->map.fill(init_item);

    this->item_ptr  = 0;
    this->address   = 0;

    load();
}



int LineMapping::add(unsigned char position, unsigned char value)
{
    sLineMapItem item;
    item.position  = position;
    item.value     = value;

    return add(item);
}


int LineMapping::add(sLineMapItem item)
{
    buffer[item_ptr%buffer.size()] = item;

    this->item_ptr++;

    if (this->item_ptr > map.size())
        return -1;

    if ((this->item_ptr%buffer.size()) == 0)
    {
        unsigned char *ch_ptr = (unsigned char*)(&(this->buffer[0]));

        eeprom.write(this->address, ch_ptr);

        this->address+= buffer.size()*sizeof(sLineMapItem);
    }

    return 0;
}

int LineMapping::get_closest(int position)
{
    unsigned int idx = 0;
    int dist_min = 0;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        int dist = map[i].position - position;
        if (dist < 0)
            dist = -dist;

        if (dist < dist_min)
        {
            dist_min = dist;
            idx = i;
        }
    }

    return map[idx].value;
}

void LineMapping::load()
{
    unsigned int address = 0;

    unsigned char *ch_ptr = (unsigned char*)(&(this->buffer[0]));

    for (unsigned int i = 0; i < map.size(); i++)
    {
        if ((i%buffer.size()) == 0)
        {
            eeprom.read(address, ch_ptr);
            address+= buffer.size()*sizeof(sLineMapItem);
        }

        map[i] = buffer[i%buffer.size()];
    }
}

void LineMapping::print()
{
    terminal << "sizeof(sLineMapItem) " << sizeof(sLineMapItem) << "\n";
    terminal << "LINE_BUFFER_SIZE " << LINE_BUFFER_SIZE << "\n";
    terminal << "LINE_MAP_SIZE " << LINE_MAP_SIZE << "\n";

    for (unsigned int i = 0; i < map.size(); i++)
    {
        int position = map[i].position;
        int value = map[i].value;
        terminal << i << " " << position << " " << value << "\n";
    }

    terminal<< "\n\n";
}

void LineMapping::print_json()
{
    terminal << "\n\n{\n";

    terminal << "\"item_size\" : " << sizeof(sLineMapItem) << ",\n";
    terminal << "\"line_buffer_size\" : " << LINE_BUFFER_SIZE << ",\n";
    terminal << "\"line_map_size\" : " << LINE_MAP_SIZE << ",\n";
    terminal << "\"map\" : [";

    for (unsigned int i = 0; i < map.size(); i++)
    {
        int position = map[i].position;
        int value = map[i].value;
        terminal << "[" << i << ", " << position << ", " << value << "]";
        if (i < map.size()-1)
            terminal << ",\n";
        else
            terminal << "\n";
    }


    terminal << "]\n";

    terminal << "}\n\n";
}
