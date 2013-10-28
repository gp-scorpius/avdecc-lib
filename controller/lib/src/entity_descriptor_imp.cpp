/*
 * Licensed under the MIT License (MIT)
 *
 * Copyright (c) 2013 AudioScience Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * entity_descriptor_imp.cpp
 *
 * Entity descriptor implementation
 */

#include <vector>
#include "enumeration.h"
#include "log.h"
#include "end_station_imp.h"
#include "entity_descriptor_imp.h"

namespace avdecc_lib
{
        entity_descriptor_imp::entity_descriptor_imp() {}

        entity_descriptor_imp::entity_descriptor_imp(end_station_imp *base_end_station_imp_ref, uint8_t *frame, size_t pos, size_t mem_buf_len) : descriptor_base_imp(base_end_station_imp_ref)
        {
                desc_entity_read_returned = jdksavdecc_descriptor_entity_read(&entity_desc, frame, pos, mem_buf_len);

                if(desc_entity_read_returned < 0)
                {
                        avdecc_lib::log_ref->logging(avdecc_lib::LOGGING_LEVEL_ERROR, "entity_desc_read error");
                        assert(desc_entity_read_returned >= 0);
                }
        }

        entity_descriptor_imp::~entity_descriptor_imp()
        {
                for(uint32_t config_vec_index = 0; config_vec_index < config_desc_vec.size(); config_vec_index++)
                {
                        delete config_desc_vec.at(config_vec_index);
                }
        }

        uint16_t STDCALL entity_descriptor_imp::get_descriptor_type()
        {
                assert(entity_desc.descriptor_type == JDKSAVDECC_DESCRIPTOR_ENTITY);
                return entity_desc.descriptor_type;
        }

        uint16_t STDCALL entity_descriptor_imp::get_descriptor_index()
        {
                assert(entity_desc.descriptor_index == 0);
                return entity_desc.descriptor_index;
        }

        uint64_t STDCALL entity_descriptor_imp::get_entity_id()
        {
                return jdksavdecc_uint64_get(&entity_desc.entity_entity_id, 0);
        }

        uint32_t STDCALL entity_descriptor_imp::get_vendor_id()
        {
                return entity_desc.vendor_id;
        }

        uint32_t STDCALL entity_descriptor_imp::get_entity_model_id()
        {
                return entity_desc.entity_model_id;
        }

        uint32_t STDCALL entity_descriptor_imp::get_entity_capabilities()
        {
                return entity_desc.entity_capabilities;
        }

        uint16_t STDCALL entity_descriptor_imp::get_talker_stream_sources()
        {
                return entity_desc.talker_stream_sources;
        }

        uint16_t STDCALL entity_descriptor_imp::get_talker_capabilities()
        {
                return entity_desc.talker_capabilities;
        }

        uint16_t STDCALL entity_descriptor_imp::get_listener_stream_sinks()
        {
                return entity_desc.listener_stream_sinks;
        }

        uint16_t STDCALL entity_descriptor_imp::get_listener_capabilities()
        {
                return entity_desc.listener_capabilities;
        }

        uint32_t STDCALL entity_descriptor_imp::get_controller_capabilities()
        {
                return entity_desc.controller_capabilities;
        }

        uint32_t STDCALL entity_descriptor_imp::get_available_index()
        {
                return entity_desc.available_index;
        }

        uint64_t STDCALL entity_descriptor_imp::get_association_id()
        {
                return jdksavdecc_uint64_get(&entity_desc.association_id, 0);
        }

        uint8_t * STDCALL entity_descriptor_imp::get_entity_name()
        {
                return entity_desc.entity_name.value;
        }

        uint16_t STDCALL entity_descriptor_imp::get_vendor_name_string()
        {
                return entity_desc.vendor_name_string;
        }

        uint16_t STDCALL entity_descriptor_imp::get_model_name_string()
        {
                return entity_desc.model_name_string;
        }

        uint8_t * STDCALL entity_descriptor_imp::get_firmware_version()
        {
                return entity_desc.firmware_version.value;
        }

        uint8_t * STDCALL entity_descriptor_imp::get_group_name()
        {
                return entity_desc.group_name.value;
        }

        uint8_t * STDCALL entity_descriptor_imp::get_serial_number()
        {
                return entity_desc.serial_number.value;
        }

        uint16_t STDCALL entity_descriptor_imp::get_configurations_count()
        {
                assert(entity_desc.configurations_count >= 1);
                return entity_desc.configurations_count;
        }

        uint16_t STDCALL entity_descriptor_imp::get_current_configuration()
        {
                return entity_desc.current_configuration;
        }

        void entity_descriptor_imp::store_config_desc(end_station_imp *base_end_station_imp_ref, uint8_t *frame, size_t pos, size_t mem_buf_len)
        {
                config_desc_vec.push_back(new configuration_descriptor_imp(base_end_station_imp_ref, frame, pos, mem_buf_len));
        }

        uint32_t STDCALL entity_descriptor_imp::get_config_desc_count()
        {
                return config_desc_vec.size();
        }

        configuration_descriptor * STDCALL entity_descriptor_imp::get_config_desc_by_index(uint16_t config_desc_index)
        {
                return config_desc_vec.at(config_desc_index);
        }

        int STDCALL entity_descriptor_imp::send_set_config_cmd()
        {

                return 0;
        }

        int STDCALL entity_descriptor_imp::send_get_config_cmd()
        {

                return 0;
        }

#ifdef DEBUG_DESCRIPTOR_FIELD_INFORMATION
        void entity_descriptor_imp::print_entity_desc_info()
        {
                std::cout << "\nEntity Descriptor";
                std::cout << "\ndescriptor_type = 0x" << std::hex << get_descriptor_type();
                std::cout << "\ndescriptor_index = 0x" << std::hex << get_descriptor_index();
                std::cout << "\nentity_id = 0x" << std::hex << get_entity_id();
                std::cout << "\nvendor_id = " << std::dec << get_vendor_id();
                std::cout << "\nentity_model_id = 0x" << std::hex << get_entity_model_id();
                std::cout << "\nentity_capabilities = 0x" << std::hex << get_entity_capabilities();
                std::cout << "\ntalker_stream_sources = 0x" << std::hex << get_talker_stream_sources();
                std::cout << "\ntalker_capabilities = 0x" << std::hex << get_talker_capabilities();
                std::cout << "\nlistener_stream_sinks = 0x" << std::hex << get_listener_stream_sinks();
                std::cout << "\nlistener_capabilities = 0x" << std::hex << get_listener_capabilities();
                std::cout << "\ncontroller_capabilities = 0x" << std::hex << get_controller_capabilities();
                std::cout << "\navailable_index = 0x" << std::hex << get_available_index();
                std::cout << "\nassociation_id = 0x" << std::hex << get_association_id();
                std::cout << "\nentity_name = " << std::dec << get_entity_name().value;
                std::cout << "\nvendor_name_string = " << std::dec << get_vendor_name_string();
                std::cout << "\nmodel_name_string = " << std::dec << get_model_name_string();
                std::cout << "\nfirmware_version = " << std::dec << get_firmware_version().value;
                std::cout << "\ngroup_name = " << std::dec << get_group_name().value;
                std::cout << "\nserial_number = " << std::dec << get_serial_number().value;
                std::cout << "\nconfigurations_count = " << std::dec << get_configurations_count();
                std::cout << "\ncurrent_configuration = " << std::dec << get_current_configuration();
        }
#endif

}