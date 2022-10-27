import { Dispatch, SetStateAction } from "react"

type SetError = Dispatch<SetStateAction<Error>>

export interface Error {
    error: boolean
    message: string
}

export const defaultError = {
    error: false,
    message: ''
}

// Possible errors
const requiredError = (value: string, setError: SetError) => {
    if (value.length === 0) {
        setError({
            error: true,
            message: 'Required*'
        })
        return false
    }
    return true
}

const emailRegex = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/
const passwordRegex = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[a-zA-Z]).{8,}$/
const invalidError = (value: string, regex: string | RegExp, setError: SetError) => {
    if (!value.match(regex)) {
        setError({
            error: true,
            message: 'Invalid'
        })
        return false
    }
    return true
}

const alreadyExistsError = (value: string, field: string, setError: SetError) => {
    // TODO: check if username or email already exists
    if (false) {
        setError({
            error: true,
            message: 'Already exists'
        })
        return false
    }
    return true
}

const passwordMatchError = (value: string, password: string, setError: SetError) => {
    if (value !== password) {
        setError({
            error: true,
            message: 'Passwords do not match'
        })
        return false
    }
    return true
}

// Validations
export const validateUsername = (value: string, setError: SetError) => {
    if (!requiredError(value, setError)) return false
    setError(defaultError)
    return true
}

export const validateEmail = (value: string, setError: SetError) => {
    if (!requiredError(value, setError)) return false
    if (!invalidError(value, emailRegex, setError)) return false
    setError(defaultError)
    return true
}

export const validatePassword = (value: string, setError: SetError) => {
    if (!requiredError(value, setError)) return false
    if (!invalidError(value, passwordRegex, setError)) return false
    setError(defaultError)
    return true
}

export const validateConfirmPassword = (value: string, password: string, setError: SetError) => {
    if (!requiredError(value, setError)) return false
    if (!passwordMatchError(value, password, setError)) return false
    setError(defaultError)
    return true
}