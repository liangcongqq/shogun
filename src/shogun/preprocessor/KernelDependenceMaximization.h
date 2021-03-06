/*
 * Copyright (c) The Shogun Machine Learning Toolbox
 * Written (w) 2014 Soumyajit De
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the Shogun Development Team.
 */

#ifndef KERNEL_DEPENDENCE_MAXIMIZATION_H__
#define KERNEL_DEPENDENCE_MAXIMIZATION_H__

#include <shogun/lib/config.h>
#include <shogun/preprocessor/DependenceMaximization.h>

namespace shogun
{

class CFeatures;
class CKernelSelection;

/** @brief Class CKernelDependenceMaximization, that uses an implementation
 * of CKernelIndependenceTest to compute dependence measures for feature
 * selection. Different kernels are used for labels and data. For the sake
 * of computational convenience, the precompute() method is overridden to
 * precompute the kernel for labels and save as an instance of CCustomKernel
 */
class CKernelDependenceMaximization : public CDependenceMaximization
{
public:
	/** Default constructor */
	CKernelDependenceMaximization();

	/** Destructor */
	virtual ~CKernelDependenceMaximization();

	/** @param kernel the kernel for features (data) */
	void set_kernel_features(CKernel* kernel);

	/** @return the kernel for features */
	CKernel* get_kernel_features() const;

	/** @param kernel the kernel for labels */
	void set_kernel_labels(CKernel* kernel);

	/** @return the kernel for labels */
	CKernel* get_kernel_labels() const;

	/**
	 * Abstract method which is overridden in the subclasses to set accepted
	 * feature selection algorithm
	 *
	 * @param algorithm the feature selection algorithm to use
	 */
	virtual void set_algorithm(EFeatureSelectionAlgorithm algorithm)=0;

	/** @return the class name */
	virtual const char* get_name() const
	{
		return "KernelDependenceMaximization";
	}

protected:
	/**
	 * Precomputes the kernel on labels and replaces the #m_kernel_labels
	 * with an instance of CCustomKernel. Labels features are set via
	 * CDependenceMaximization::set_labels call.
	 */
	virtual void precompute();

	/** The kernel for data (features) to be used in CKernelIndependenceTest */
	CKernel* m_kernel_features;

	/** The kernel for labels to be used in CKernelIndependenceTest */
	CKernel* m_kernel_labels;

private:
	/** Register params and initialize with default values */
	void initialize_parameters();

};

}
#endif // KERNEL_DEPENDENCE_MAXIMIZATION_H__
