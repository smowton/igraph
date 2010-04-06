/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2009  Gabor Csardi <csardi@rmki.kfki.hu>
   MTA RMKI, Konkoly-Thege Miklos st. 29-33, Budapest 1121, Hungary
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#ifndef IGRAPH_COMMUNITY_H
#define IGRAPH_COMMUNITY_H

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

#include "igraph_constants.h"
#include "igraph_datatype.h"
#include "igraph_types.h"
#include "igraph_arpack.h"

__BEGIN_DECLS

/* -------------------------------------------------- */
/* K-Cores                                            */
/* -------------------------------------------------- */

int igraph_coreness(const igraph_t *graph, igraph_vector_t *cores,
		    igraph_neimode_t mode);

/* -------------------------------------------------- */
/* Community Structure                                */
/* -------------------------------------------------- */

/* TODO: cut.community */
/* TODO: edge.type.matrix */
/* TODO:  */

int igraph_community_optimal_modularity(const igraph_t *graph,
					igraph_real_t *modularity,
					igraph_vector_t *membership,
					igraph_bool_t verbose);

int igraph_community_spinglass(const igraph_t *graph,
			       const igraph_vector_t *weights,
			       igraph_real_t *modularity,
			       igraph_real_t *temperature,
			       igraph_vector_t *membership, 
			       igraph_vector_t *csize, 
			       igraph_integer_t spins,
			       igraph_bool_t parupdate,
			       igraph_real_t starttemp,
			       igraph_real_t stoptemp,
			       igraph_real_t coolfact,
			       igraph_spincomm_update_t update_rule,
			       igraph_real_t gamma, 
			       /* the rest is for the NegSpin implementation */
			       igraph_spinglass_implementation_t implementation,
/* 			       igraph_matrix_t *adhesion, */
/* 			       igraph_matrix_t *normalised_adhesion, */
/* 			       igraph_real_t *polarization, */
			       igraph_real_t lambda);

int igraph_community_spinglass_single(const igraph_t *graph,
				      const igraph_vector_t *weights,
				      igraph_integer_t vertex,
				      igraph_vector_t *community,
				      igraph_real_t *cohesion,
				      igraph_real_t *adhesion,
				      igraph_integer_t *inner_links,
				      igraph_integer_t *outer_links,
				      igraph_integer_t spins,
				      igraph_spincomm_update_t update_rule,
				      igraph_real_t gamma);
				   
int igraph_community_walktrap(const igraph_t *graph, 
			      const igraph_vector_t *weights,
			      int steps,
			      igraph_matrix_t *merges,
			      igraph_vector_t *modularity);

int igraph_community_edge_betweenness(const igraph_t *graph, 
				      igraph_vector_t *result,
				      igraph_vector_t *edge_betweenness,
				      igraph_matrix_t *merges,
				      igraph_vector_t *bridges,
				      igraph_bool_t directed);
int igraph_community_eb_get_merges(const igraph_t *graph, 
				   const igraph_vector_t *edges,
				   igraph_matrix_t *merges,
				   igraph_vector_t *bridges);

int igraph_community_fastgreedy(const igraph_t *graph,
				const igraph_vector_t *weights,
				igraph_matrix_t *merges,
				igraph_vector_t *modularity);

int igraph_community_to_membership(const igraph_matrix_t *merges,
				   igraph_integer_t nodes,
				   igraph_integer_t steps,
				   igraph_vector_t *membership,
				   igraph_vector_t *csize);
int igraph_le_community_to_membership(const igraph_matrix_t *merges,
				      igraph_integer_t steps,
				      igraph_vector_t *membership,
				      igraph_vector_t *csize);

int igraph_modularity(const igraph_t *graph, 
		      const igraph_vector_t *membership,
		      igraph_real_t *modularity,
              const igraph_vector_t *weights);

int igraph_reindex_membership(igraph_vector_t *membership,
                              igraph_vector_t *new_to_old);

int igraph_community_leading_eigenvector_naive(const igraph_t *graph,
					       igraph_matrix_t *merges,
					       igraph_vector_t *membership,
					       igraph_integer_t steps,
					       igraph_arpack_options_t *options);
int igraph_community_leading_eigenvector(const igraph_t *graph,
					 igraph_matrix_t *merges,
					 igraph_vector_t *membership,
					 igraph_integer_t steps,
					 igraph_arpack_options_t *options);
int igraph_community_leading_eigenvector_step(const igraph_t *graph,
					      igraph_vector_t *membership,
					      igraph_integer_t community,
					      igraph_bool_t *split,
					      igraph_vector_t *eigenvector,
					      igraph_real_t *eigenvalue, 
					      igraph_arpack_options_t *options,
					      igraph_arpack_storage_t *storage);
int igraph_community_label_propagation(const igraph_t *graph,
                                       igraph_vector_t *membership,
                                       const igraph_vector_t *weights,
                                       const igraph_vector_t *initial,
                                       igraph_vector_bool_t *fixed);
int igraph_community_multilevel(const igraph_t *graph,
                                const igraph_vector_t *weights,
                                igraph_vector_t *membership,
                                igraph_matrix_t *memberships,
                                igraph_vector_t *modularity);

/* -------------------------------------------------- */
/* Community Structure Comparison                     */
/* -------------------------------------------------- */

int igraph_compare_communities(const igraph_vector_t *comm1,
	                       const igraph_vector_t *comm2,
			       igraph_real_t* result,
			       igraph_community_comparison_t method);

__END_DECLS

#endif
