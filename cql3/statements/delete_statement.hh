/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Copyright 2015 Cloudius Systems
 *
 * Modified by Cloudius Systems
 */

/*
 * This file is part of Scylla.
 *
 * Scylla is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Scylla is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Scylla.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "cql3/statements/modification_statement.hh"
#include "cql3/attributes.hh"
#include "cql3/operation.hh"
#include "database_fwd.hh"

namespace cql3 {

namespace statements {

/**
* A <code>DELETE</code> parsed from a CQL query statement.
*/
class delete_statement : public modification_statement {
public:
    delete_statement(statement_type type, uint32_t bound_terms, schema_ptr s, std::unique_ptr<attributes> attrs);

    virtual bool require_full_clustering_key() const override;

    virtual void add_update_for_key(mutation& m, const exploded_clustering_prefix& prefix, const update_parameters& params) override;

#if 0
    protected void validateWhereClauseForConditions() throws InvalidRequestException
    {
        Iterator<ColumnDefinition> iterator = Iterators.concat(cfm.partitionKeyColumns().iterator(), cfm.clusteringColumns().iterator());
        while (iterator.hasNext())
        {
            ColumnDefinition def = iterator.next();
            Restriction restriction = processedKeys.get(def.name);
            if (restriction == null || !(restriction.isEQ() || restriction.isIN()))
            {
                throw new InvalidRequestException(
                        String.format("DELETE statements must restrict all PRIMARY KEY columns with equality relations in order " +
                                      "to use IF conditions, but column '%s' is not restricted", def.name));
            }
        }

    }
#endif

    class parsed : public modification_statement::parsed {
    private:
        std::vector<::shared_ptr<operation::raw_deletion>> _deletions;
        std::vector<::shared_ptr<relation>> _where_clause;
    public:
        parsed(::shared_ptr<cf_name> name,
               ::shared_ptr<attributes::raw> attrs,
               std::vector<::shared_ptr<operation::raw_deletion>> deletions,
               std::vector<::shared_ptr<relation>> where_clause,
               conditions_vector conditions,
               bool if_exists);
    protected:
        virtual ::shared_ptr<modification_statement> prepare_internal(database& db, schema_ptr schema,
            ::shared_ptr<variable_specifications> bound_names, std::unique_ptr<attributes> attrs);
    };
};

}

}
